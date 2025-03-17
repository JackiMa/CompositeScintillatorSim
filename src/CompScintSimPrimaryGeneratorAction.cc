#include "CompScintSimPrimaryGeneratorAction.hh"
#include "CompScintSimPrimaryGeneratorMessenger.hh"

#include "G4Event.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"

#include "Randomize.hh"

#include "utilities.hh"
#include "MyPhysicalVolume.hh"
#include "config.hh"
#include <iomanip>
#include <mutex>  // 添加互斥锁的头文件

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
CompScintSimPrimaryGeneratorAction::CompScintSimPrimaryGeneratorAction(CompScintSimDetectorConstruction *detectorConstruction)
    : G4VUserPrimaryGeneratorAction(), fParticleGun(nullptr), useParticleGun(false), fDetectorConstruction(detectorConstruction), fCurrentEventIndex(0), fTotalParticleCount(0)
{
  fGunMessenger = new CompScintSimPrimaryGeneratorMessenger(this);

  // Initialize parameters
  G4int n_particle = 1;
  G4ParticleDefinition *particle = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
  G4ThreeVector source_position = G4ThreeVector(0., 0., 10 * cm);
  G4double energy = 0.1 * keV;

  // ParticleGun
  fParticleGun = new G4ParticleGun(n_particle);
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticlePosition(source_position);
  fParticleGun->SetParticleEnergy(energy);

  // GPS
  fGPS = new G4GeneralParticleSource();
  fGPS->SetParticleDefinition(particle);
  fGPS->GetCurrentSource()->GetPosDist()->SetCentreCoords(source_position);
  fGPS->GetCurrentSource()->GetEneDist()->SetMonoEnergy(energy);
  fGPS->GetCurrentSource()->GetAngDist()->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));

  // 初始化随机数生成器
  gen.seed(static_cast<unsigned long>(time(nullptr)));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
CompScintSimPrimaryGeneratorAction::~CompScintSimPrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fGPS;
  delete fGunMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void CompScintSimPrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
  // 初始化投影区域（如果尚未初始化）
  G4RunManager *runManager = G4RunManager::GetRunManager();
  auto analysisManager = G4AnalysisManager::Instance();
  detector = dynamic_cast<const CompScintSimDetectorConstruction *>(runManager->GetUserDetectorConstruction());
  if (!detector)
  {
    G4ExceptionDescription msg;
    msg << "Detector construction is not found!";
    G4Exception("CompScintSimPrimaryGeneratorAction::GeneratePrimaries()", "CompScintSim_001", FatalException, msg);
  }

  InitializeProjectionArea();

  // 根据选择使用ParticleGun或自定义GPS源
  if (useParticleGun)
  {
    // 使用ParticleGun（保持原有逻辑）
    // 在投影区域内随机抽样一个点
    G4double x = disX(gen);
    G4double y = disY(gen);

    // 将抽样得到的放射源位置XY填入到H2中
    analysisManager->FillH2(0, x, y);

    MyPhysicalVolume *p_shield = detector->GetMyVolume("scint_layer_1");
    G4Box *shield_box = dynamic_cast<G4Box *>(p_shield->GetLogicalVolume()->GetSolid());
    z_pos = p_shield->GetAbsolutePosition().z() + shield_box->GetZHalfLength() + 5 * mm;

    G4ThreeVector sourcePosition(x, y, z_pos);
    G4ThreeVector direction(0, 0, -1);

    fParticleGun->SetParticlePosition(sourcePosition);
    fParticleGun->SetParticleMomentumDirection(direction);
    fParticleGun->GeneratePrimaryVertex(anEvent);

    myPrint(DEBUG, fmt("ParticleGun generated a particle: pos=({},{},{}), dir=({},{},{})",
                       sourcePosition.x(), sourcePosition.y(), sourcePosition.z(),
                       direction.x(), direction.y(), direction.z()));
  }
  else
  {
    // 使用自定义GPS源
    // 如果GPS源列表为空，使用默认的GPS配置
    if (fGPSSources.empty())
    {
      // 在投影区域内随机抽样一个点
      G4double x = disX(gen);
      G4double y = disY(gen);

      // 将抽样得到的放射源位置XY填入到H2中
      analysisManager->FillH2(0, x, y);

      MyPhysicalVolume *p_shield = detector->GetMyVolume("scint_layer_1");
      G4Box *shield_box = dynamic_cast<G4Box *>(p_shield->GetLogicalVolume()->GetSolid());
      z_pos = p_shield->GetAbsolutePosition().z() + shield_box->GetZHalfLength() + 5 * mm;

      G4ThreeVector sourcePosition(x, y, z_pos);
      G4ThreeVector direction(0, 0, -1);

      fGPS->GetCurrentSource()->GetPosDist()->SetPosDisType("Point");
      fGPS->GetCurrentSource()->GetPosDist()->SetCentreCoords(sourcePosition);
      fGPS->GetCurrentSource()->GetAngDist()->SetParticleMomentumDirection(direction);
      fGPS->GeneratePrimaryVertex(anEvent);

      myPrint(DEBUG, fmt("Default GPS generated a particle: pos=({},{},{}), dir=({},{},{})",
                         sourcePosition.x(), sourcePosition.y(), sourcePosition.z(),
                         direction.x(), direction.y(), direction.z()));
      return;
    }

    // 检查是否有定义的粒子源
    if (fTotalParticleCount == 0)
    {
      myPrint(ERROR, "No particles defined in sources. Using default GPS configuration.");
      return;
    }

    // 确定当前事件对应的源索引
    G4int eventID = anEvent->GetEventID();
    myPrint(DEBUG, fmt("Processing event ID: {}", eventID));

    // 在每个beamOn命令中生成所有的粒子
    // 遍历所有源并生成其对应的粒子
    for (size_t sourceIndex = 0; sourceIndex < fGPSSources.size(); sourceIndex++)
    {
      const MyGPSSource &source = fGPSSources[sourceIndex];

      // 获取粒子定义
      G4ParticleDefinition *particleDef =
          G4ParticleTable::GetParticleTable()->FindParticle(source.particleType);

      if (!particleDef)
      {
        myPrint(ERROR, fmt("WARNING: Particle type {} not found! Skipping this source.", source.particleType));
        continue;
      }

      myPrint(DEBUG, fmt("Processing source {}: {} particles, energy {} MeV, {} particles",
                         source.id, source.particleType, source.energy / MeV, source.count));

      MyPhysicalVolume *p_shield = detector->GetMyVolume("scint_layer_1");
      G4Box *shield_box = dynamic_cast<G4Box *>(p_shield->GetLogicalVolume()->GetSolid());
      z_pos = p_shield->GetAbsolutePosition().z() + shield_box->GetZHalfLength() + 5 * mm;
      G4ThreeVector direction(0, 0, -1);
      fGPS->GetCurrentSource()->GetPosDist()->SetPosDisType("Point");
      fGPS->GetCurrentSource()->GetAngDist()->SetParticleMomentumDirection(direction);

      // 为该源生成指定数量的粒子
      G4int total_generated_particles = 0;
      for (G4int i = 0; i < source.count; i++)
      {
        // 在投影区域内随机抽样一个点
        G4double x = disX(gen);
        G4double y = disY(gen);

        // 将抽样得到的放射源位置XY填入到H2中
        analysisManager->FillH2(0, x, y);

        G4ThreeVector sourcePosition(x, y, z_pos);

        // 获取互斥锁，保护GPS配置和粒子生成过程
        std::lock_guard<std::mutex> lock(fGPSMutex);
        
        // 配置GPS
        fGPS->SetParticleDefinition(particleDef);
        fGPS->GetCurrentSource()->GetEneDist()->SetMonoEnergy(source.energy);
        fGPS->GetCurrentSource()->GetPosDist()->SetCentreCoords(sourcePosition);

        // 生成粒子
        fGPS->GeneratePrimaryVertex(anEvent);
        
        // 锁会在此作用域结束时自动释放

        myPrint(DEBUG, fmt("Source {} generated particle {}/{}: {} {} MeV, pos=({},{},{})",
                           source.id, i + 1, source.count, source.particleType, source.energy / MeV,
                           sourcePosition.x(), sourcePosition.y(), sourcePosition.z()));
        total_generated_particles++;
      }

      myPrint(DEBUG, fmt("Completed source {}: {} particles ({} particles generated)",
                         source.id, source.particleType, total_generated_particles));
    }

    myPrint(INFO, fmt("Event {} completed: Total generated {} particles", eventID, fTotalParticleCount));
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// GPS源管理方法
void CompScintSimPrimaryGeneratorAction::AddGPSSource(const G4String &particleType, G4double energy, G4int count)
{
  // 使用当前源的数量作为新源的ID
  G4int newSourceId = fGPSSources.size();
  fGPSSources.push_back(MyGPSSource(newSourceId, particleType, energy, count));
  // 更新总粒子数
  fTotalParticleCount += count;
  // 重置当前事件索引
  fCurrentEventIndex = 0;
}

void CompScintSimPrimaryGeneratorAction::ClearGPSSources()
{
  fGPSSources.clear();
  fTotalParticleCount = 0;
  fCurrentEventIndex = 0;
}

void CompScintSimPrimaryGeneratorAction::ListGPSSources() const
{
  myPrint(DEBUG, "ListGPSSources method called");
  G4cout << "=== Custom Particle Sources List ===" << G4endl;

  if (fGPSSources.empty())
  {
    G4cout << "No particle sources defined." << G4endl;
  }
  else
  {
    for (const auto &source : fGPSSources)
    {
      G4cout << "my_source " << source.id << ": "
             << source.particleType << " "
             << source.energy / MeV << " MeV "
             << source.count << " counts/per" << G4endl;
    }

    // 计算总粒子数
    G4int totalCount = 0;
    for (const auto &source : fGPSSources)
    {
      totalCount += source.count;
    }

    G4cout << "Total sources: " << fGPSSources.size() << G4endl;
    G4cout << "Total particles: " << totalCount << G4endl;
  }

  G4cout << "=========================" << G4endl;
}

void CompScintSimPrimaryGeneratorAction::SetUseParticleGun(G4bool useGun)
{
  useParticleGun = useGun;
}

void CompScintSimPrimaryGeneratorAction::InitializeProjectionArea()
{

  if (isInitialized)
    return;
  isInitialized = true;
  // 获取闪烁体的位置和形状
  MyPhysicalVolume *physicalScintillator = detector->GetMyVolume("scint_layer_1");
  G4ThreeVector position = physicalScintillator->GetAbsolutePosition();
  G4VSolid *solid = physicalScintillator->GetLogicalVolume()->GetSolid();
  G4RotationMatrix *rotation = physicalScintillator->GetAbsoluteRotation();

  if (G4Box *box = dynamic_cast<G4Box *>(solid))
  {
    // 闪烁体是 G4Box
    G4double halfX = box->GetXHalfLength();
    G4double halfY = box->GetYHalfLength();
    G4double halfZ = box->GetZHalfLength();

    // 计算投影区域
    G4ThreeVector corners[8] = {
        G4ThreeVector(-halfX, -halfY, -halfZ),
        G4ThreeVector(halfX, -halfY, -halfZ),
        G4ThreeVector(-halfX, halfY, -halfZ),
        G4ThreeVector(halfX, halfY, -halfZ),
        G4ThreeVector(-halfX, -halfY, halfZ),
        G4ThreeVector(halfX, -halfY, halfZ),
        G4ThreeVector(-halfX, halfY, halfZ),
        G4ThreeVector(halfX, halfY, halfZ)};

    minX = DBL_MAX, maxX = -DBL_MAX;
    minY = DBL_MAX, maxY = -DBL_MAX;

    for (auto &corner : corners)
    {
      if (rotation)
      {
        corner = (*rotation) * corner;
      }
      corner += position;
      if (corner.x() < minX)
        minX = corner.x();
      if (corner.x() > maxX)
        maxX = corner.x();
      if (corner.y() < minY)
        minY = corner.y();
      if (corner.y() > maxY)
        maxY = corner.y();
    }
  }
  else if (G4Tubs *tubs = dynamic_cast<G4Tubs *>(solid))
  {
    // 闪烁体是 G4Tubs
    G4double rMax = tubs->GetOuterRadius();
    G4double halfZ = tubs->GetZHalfLength();
    // 默认圆柱体都是竖着的，所以halfZ就是圆柱体的半长度

    // 计算投影区域
    minX = position.x() - halfZ;
    maxX = position.x() + halfZ;
    minY = position.y() - rMax;
    maxY = position.y() + rMax;
  }
  else
  {
    G4ExceptionDescription msg;
    msg << "Invalid entity type, current entity type is: " << solid->GetEntityType();
    G4Exception("CompScintSimPrimaryGeneratorAction::InitializeProjectionArea()",
                "CompScintSim_001", FatalException, msg);
  }

  // 计算原来的中心点
  G4double centerX = 0.5 * (minX + maxX);
  G4double centerY = 0.5 * (minY + maxY);

  // 计算新的范围
  G4double newMinX = centerX - (centerX - minX) * g_source_scale;
  G4double newMaxX = centerX + (maxX - centerX) * g_source_scale;
  G4double newMinY = centerY - (centerY - minY) * g_source_scale;
  G4double newMaxY = centerY + (maxY - centerY) * g_source_scale;

  // 创建新的分布
  disX = std::uniform_real_distribution<>(newMinX, newMaxX);
  disY = std::uniform_real_distribution<>(newMinY, newMaxY);

  G4cout << "Projection area initialized: " << minX << " " << maxX << " " << minY << " " << maxY << G4endl;
}

// 定义静态互斥锁
std::mutex CompScintSimPrimaryGeneratorAction::fGPSMutex;