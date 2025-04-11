#include <vector>

#include "CompScintSimDetectorConstruction.hh"
#include "CompScintSimDetectorMessenger.hh"
#include "CompScintSimLayerSensitiveDetector.hh"
#include "MaterialManager.hh"
#include "ScintillatorLayerManager.hh"

#include "G4Element.hh"
#include "G4GDMLParser.hh"
#include "G4Box.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalVolume.hh"
#include "G4OpticalSurface.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4AssemblyVolume.hh"

#include "G4GlobalMagFieldMessenger.hh"
#include "G4SDManager.hh"
#include "G4SDChargedFilter.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4Exception.hh"
#include "G4AnalysisManager.hh"

#include "MyMaterials.hh"
#include "MyPhysicalVolume.hh"
#include "CustomScorer.hh"
#include "utilities.hh"
#include "config.hh"

std::vector<G4ThreeVector> generateCoordinates(int nums, double gaps);

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// 在这里对类相关参数进行初始化
CompScintSimDetectorConstruction::CompScintSimDetectorConstruction()
    : G4VUserDetectorConstruction()
{
  fDumpGdmlFileName = "LightCollecion.gdml";
  fVerbose = false;  // 是否输出详细信息
  fDumpGdml = false; // 是否保存GDML的几何文件
  // create a messenger for this class
  fDetectorMessenger = new CompScintSimDetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
CompScintSimDetectorConstruction::~CompScintSimDetectorConstruction()
{
  delete fDetectorMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VPhysicalVolume *CompScintSimDetectorConstruction::Construct()
{
  G4bool checkOverlaps = true;

  // ------------- Volumes --------------
  // s_ for soild_
  // l_ for logical_
  // p_ for physical_
  //
  // The world
  G4Box *s_world = new G4Box("World", 0.5 * g_worldX, 0.5 * g_worldY, 0.5 * g_worldZ);
  G4LogicalVolume *l_world = new G4LogicalVolume(s_world, g_world_material, "World");
  MyPhysicalVolume *p_world = new MyPhysicalVolume(nullptr, G4ThreeVector(), "World", l_world, nullptr, false, 0, checkOverlaps);

  // 构建闪烁体探测器层
  // 使用ScintillatorLayerManager来管理闪烁体层参数

  // 初始化闪烁体层管理器
  ScintillatorLayerManager &layerManager = ScintillatorLayerManager::GetInstance();


  // 获取闪烁体层总高度
  G4double total_stack_height = layerManager.GetTotalStackHeight() * mm;

  // 计算起始Z位置，使堆叠居中
  G4double z_position = -total_stack_height / 2.0;

  // 获取所有层的copynumber列表并使用
  const std::vector<G4int> &copynumbers = layerManager.GetCopynumbers();

  // 反向迭代copynumbers，确保从上到下的顺序处理
  for (auto it = copynumbers.rbegin(); it != copynumbers.rend(); ++it)
  {
    G4int copynumber = *it;
    const ScintillatorLayerInfo *layerInfo = layerManager.GetLayerInfo(copynumber);

    if (!layerInfo)
    {
      G4ExceptionDescription ed;
      ed << "Failed to get layer info for copynumber " << copynumber;
      G4Exception("CompScintSimDetectorConstruction::Construct",
                  "LayerNotFound", FatalException, ed);
      continue;
    }

    G4cout << "Creating layer " << copynumber << " scintillator detector..." << G4endl;

    // 计算层的放置位置
    G4double layer_height = layerInfo->GetScintHeightMM() + 2 * layerInfo->GetCoatingThicknessNM();
    G4ThreeVector layer_position = G4ThreeVector(0, 0, z_position + 0.5 * layer_height);

    // 构建闪烁体探测器层
    MyPhysicalVolume *p_layer = BuildScintillatorLayer(
        copynumber,
        layerInfo->readout_face,
        layerInfo->scint_material,
        layerInfo->scint_lightyield,
        layerInfo->GetScintLengthMM(),
        layerInfo->GetScintWidthMM(),
        layerInfo->GetScintHeightMM(),
        layerInfo->GetCoatingThicknessNM(),
        layerInfo->coating_material,
        layerInfo->GetFiberCoreDiameterUM(),
        layerInfo->GetFiberCladdingDiameterUM(),
        p_world,
        layer_position);

    // 添加到体积映射
    G4String phys_name = "Layer_" + std::to_string(copynumber) + "_phys";
    fVolumeMap[phys_name] = p_layer;

    // 更新z位置用于下一层
    z_position += layer_height + g_scint_layer_gap;
  }

  G4cout << "Multi-layer scintillator detector construction complete, total z-position: 0 - " << z_position << " mm" << G4endl;

  // 打印fVolumeMap，这是用来索引不同几何体绝对坐标的
  myPrint(DEBUG, f("fVolumeMap length is {}\n", fVolumeMap.size()));
  for (const auto &pair : fVolumeMap)
  {
    std::cout << "Volume name: " << pair.first << ", Volume address: " << pair.second << std::endl;
  }

  if (fDumpGdml)
  {
    std::ifstream ifile(fDumpGdmlFileName);
    if (ifile)
    {
      G4cout << fDumpGdmlFileName << " already exists, will not overwrite." << G4endl;
    }
    else
    {
      G4GDMLParser *parser = new G4GDMLParser();
      parser->Write(fDumpGdmlFileName, p_world);
    }
  }

  return p_world;
}

MyPhysicalVolume *CompScintSimDetectorConstruction::GetMyVolume(G4String volumeName) const
{
  auto it = fVolumeMap.find(volumeName);
  if (it != fVolumeMap.end())
  {
    myPrint(DEBUG, fmt("{} Volume is found!\n", volumeName));
    return it->second;
  }
  else
  {
    myPrint(ERROR, fmt("{} Volume not found!\n", volumeName));
    G4Exception("CompScintSimDetectorConstruction::GetMyVolume",
                "VolumeNotFound", FatalException,
                ("Volume " + volumeName + " not found in the volume map.").c_str());
    return nullptr; // 这行代码实际上不会被执行，因为G4Exception会终止程序
  }
}

void CompScintSimDetectorConstruction::ConstructSDandField()
{
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
  G4VPrimitiveScorer *primitive;

  ScintillatorLayerManager &layerManager = ScintillatorLayerManager::GetInstance();
  std::vector<G4int> id_lists = layerManager.GetCopynumbers();
  for (const auto &id : id_lists)
  {
    G4String layer_name = "scint_layer_" + std::to_string(id);
    G4String fiber_name = "fiber_core_" + std::to_string(id);

    // 使用目录结构命名
    G4String layerPrefix = "Layer_" + std::to_string(id) + "_";

    auto layer = new G4MultiFunctionalDetector(layer_name);
    auto fiber = new G4MultiFunctionalDetector(fiber_name);
    G4SDManager::GetSDMpointer()->AddNewDetector(layer);
    G4SDManager::GetSDMpointer()->AddNewDetector(fiber);

    // 注册能量沉积探测器
    primitive = new G4PSEnergyDeposit("TotalEnergy");
    layer->RegisterPrimitive(primitive);

    // 自上而下穿过该层的总能量的探测器(Truely，避免多次散射多次穿越时的重复统计)
    primitive = new TruelyPassingEnergyScorer("TruelyPassingEnergy", layer_name);
    layer->RegisterPrimitive(primitive);

    // 注册光子探测器 - 闪烁光
    primitive = new SCLightScorer("ScintillationPhotons", 
                                  G4AnalysisManager::Instance()->GetH1Id(layerPrefix + "Scint"));
    layer->RegisterPrimitive(primitive);

    // 注册光子探测器 - 切伦科夫光
    primitive = new CherenkovLightScorer("CherenkovPhotons", 
                                        G4AnalysisManager::Instance()->GetH1Id(layerPrefix + "Chrnkv"));
    layer->RegisterPrimitive(primitive);

    SetSensitiveDetector(layer_name, layer);
    
    // // 注册光子探测器 - 进入NA的光子
    // primitive = new FiberAcceptanceScorer("FiberNAPhotons", 
    //                                      G4AnalysisManager::Instance()->GetH1Id(layerPrefix + "FiberNA"));
    // layer->RegisterPrimitive(primitive);

    // 注册光子探测器 - 进入光纤的光子
    primitive = new FiberEntryPhotonScorer("FiberEntryPhotons", 
                                          G4AnalysisManager::Instance()->GetH1Id(layerPrefix + "FiberEntry"));
    fiber->RegisterPrimitive(primitive);
    SetSensitiveDetector(fiber_name, fiber);

  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void CompScintSimDetectorConstruction::SetDumpGdml(G4bool val) { fDumpGdml = val; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool CompScintSimDetectorConstruction::IsDumpGdml() const { return fDumpGdml; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void CompScintSimDetectorConstruction::SetVerbose(G4bool val) { fVerbose = val; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool CompScintSimDetectorConstruction::IsVerbose() const { return fVerbose; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void CompScintSimDetectorConstruction::SetDumpGdmlFile(G4String filename)
{
  fDumpGdmlFileName = filename;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4String CompScintSimDetectorConstruction::GetDumpGdmlFile() const
{
  return fDumpGdmlFileName;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void CompScintSimDetectorConstruction::PrintError(G4String ed)
{
  G4Exception("CompScintSimDetectorConstruction:MaterialProperty test", "op001",
              FatalException, ed);
}

/**
 * @brief 构建单个闪烁体探测器层
 *
 * 该函数根据CSV文件中的参数创建一个闪烁体探测器层，包括：
 * 1. 外层coating材料包装
 * 2. 内部闪烁体晶体
 * 3. 读出光纤（含芯和包层）
 * 4. 根据readout_face参数设置光纤方向（0-3分别对应0°、90°、180°、270°）
 *
 * @param copynumber 探测器编号
 * @param readout_face 读出面方向(0-3)
 * @param scint_material_name 闪烁体材料名称
 * @param scint_lightyield 闪烁体光产额
 * @param scint_length_mm 闪烁体长度(mm)
 * @param scint_width_mm 闪烁体宽度(mm)
 * @param scint_height_mm 闪烁体高度(mm)
 * @param coating_thickness_nm coating厚度(nm)
 * @param coating_material_name coating材料名称
 * @param fiber_core_diameter_um 光纤芯直径(um)
 * @param fiber_cladding_diameter_um 光纤包层直径(um)
 * @param mother_phys 母体物理体
 * @param position 放置位置
 * @return MyPhysicalVolume* 构建好的探测器层物理体
 */
MyPhysicalVolume *CompScintSimDetectorConstruction::BuildScintillatorLayer(
    G4int copynumber,
    G4int readout_face,
    G4String scint_material_name,
    G4double scint_lightyield,
    G4double scint_length_mm,
    G4double scint_width_mm,
    G4double scint_height_mm,
    G4double coating_thickness_nm,
    G4String coating_material_name,
    G4double fiber_core_diameter_um,
    G4double fiber_cladding_diameter_um,
    MyPhysicalVolume *mother_phys,
    G4ThreeVector position)
{
  // 检查参数
  G4bool checkOverlaps = true;

  // 参数校验
  if (fiber_core_diameter_um >= fiber_cladding_diameter_um)
  {
    G4ExceptionDescription ed;
    ed << "Fiber core diameter (" << fiber_core_diameter_um
       << "um) must be smaller than cladding diameter (" << fiber_cladding_diameter_um << "um)";
    G4Exception("CompScintSimDetectorConstruction::BuildScintillatorLayer",
                "InvalidParameters", FatalException, ed);
  }

  // 转换单位(传入的已经是转换单位后的结果，所以这里直接赋值)
  G4double scint_length = scint_length_mm;
  G4double scint_width = scint_width_mm;
  G4double scint_height = scint_height_mm;
  G4double coating_thickness = coating_thickness_nm;
  G4double fiber_core_diameter = fiber_core_diameter_um;
  G4double fiber_cladding_diameter = fiber_cladding_diameter_um;

  // 检查光纤孔是否能开在coating+scintillator的总厚度内
  G4double hole_diameter = fiber_cladding_diameter * g_hole_diameter_ratio;
  G4double total_thickness = scint_height + 2 * coating_thickness;

  // 检查孔径是否超过总厚度
  if (hole_diameter > total_thickness)
  {
    G4cout << "WARNING: Fiber hole diameter (" << hole_diameter / mm
           << "mm) is larger than the total thickness in readout direction ("
           << total_thickness / mm << "mm). This may affect detector performance." << G4endl;
  }

  // 动态创建材料
  G4Material *scintMaterial = MaterialManager::GetScintillator(
      scint_material_name, scint_lightyield, 1000, -1);

  // 创建coating材料
  G4Material *coatingMaterial = MaterialManager::GetMaterial(coating_material_name);

  // 创建光纤材料
  G4Material *s_fiberCoreMaterial = MyMaterials::Quartz();
  G4Material *s_fiberCladdingMaterial = MyMaterials::PVC();

  // 计算总尺寸（包括coating）
  G4double total_length = scint_length + 2 * coating_thickness;
  G4double total_width = scint_width + 2 * coating_thickness;
  G4double total_height = scint_height + 2 * coating_thickness;

  // 创建layer box
  G4String layerName = "Layer_" + std::to_string(copynumber);
  G4Box *s_layer = new G4Box(layerName, 0.5 * total_length, 0.5 * total_width, 0.5 * total_height);

  // 创建coating box
  G4String coatingName = "Coating_" + std::to_string(copynumber);
  G4Box *s_coating = new G4Box(coatingName, 0.5 * total_length, 0.5 * total_width, 0.5 * total_height);

  // 为光纤创建hole
  G4Tubs *s_hole = new G4Tubs("hole", 0, 0.5 * hole_diameter, coating_thickness, 0, 360 * deg);

  // 根据readout_face确定hole位置和旋转
  G4RotationMatrix *hole_rot = new G4RotationMatrix();
  G4ThreeVector hole_pos;

  switch (readout_face)
  {
  case 0: // 默认方向（+X面）
    hole_rot->rotateY(90 * deg);
    hole_pos = G4ThreeVector(0.5 * total_length, 0, 0);
    break;
  case 1: // 旋转90°（+Y面）
    hole_rot->rotateX(90 * deg);
    hole_pos = G4ThreeVector(0, 0.5 * total_width, 0);
    break;
  case 2: // 旋转180°（-X面）
    hole_rot->rotateY(90 * deg);
    hole_pos = G4ThreeVector(-0.5 * total_length, 0, 0);
    break;
  case 3: // 旋转270°（-Y面）
    hole_rot->rotateX(90 * deg);
    hole_pos = G4ThreeVector(0, -0.5 * total_width, 0);
    break;
  default:
    G4ExceptionDescription ed;
    ed << "Invalid readout_face value: " << readout_face << ", must be 0, 1, 2, or 3";
    G4Exception("CompScintSimDetectorConstruction::BuildScintillatorLayer",
                "InvalidReadoutFace", FatalException, ed);
  }

  // 从layer中切掉hole
  G4SubtractionSolid *s_layer_with_hole = new G4SubtractionSolid(
      layerName + "_with_hole", s_layer, s_hole, hole_rot, hole_pos);
  G4LogicalVolume *l_layer = new G4LogicalVolume(
      s_layer_with_hole, g_world_material, layerName + "_logic");
  // 创建layer物理体
  G4String phys_name = "Layer_" + std::to_string(copynumber) + "_phys";
  MyPhysicalVolume *p_layer = new MyPhysicalVolume(
      nullptr, position, phys_name, l_layer, mother_phys, false, copynumber, checkOverlaps);

  // 从coating中切掉hole
  G4SubtractionSolid *s_coating_with_hole = new G4SubtractionSolid(
      coatingName + "_with_hole", s_coating, s_hole, hole_rot, hole_pos);

  // 创建coating逻辑体
  G4LogicalVolume *l_coating = new G4LogicalVolume(
      s_coating_with_hole, coatingMaterial, coatingName + "_logic");

  // 设置coating的可视化属性（灰色，50%透明度）
  G4VisAttributes *coating_vis = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.5));
  coating_vis->SetForceSolid(true);
  l_coating->SetVisAttributes(coating_vis);

  // 创建闪烁体
  G4String scintName = "scint_layer_" + std::to_string(copynumber);
  G4Box *s_scint = new G4Box(scintName, 0.5 * scint_length, 0.5 * scint_width, 0.5 * scint_height);
  G4LogicalVolume *l_scint = new G4LogicalVolume(
      s_scint, scintMaterial, scintName );

  // 设置闪烁体的可视化属性（橙色）
  G4VisAttributes *scint_vis = new G4VisAttributes(G4Colour(1.0, 0.65, 0, 0.5));
  scint_vis->SetForceSolid(true);
  l_scint->SetVisAttributes(scint_vis);

  // 将coating放入layer
  MyPhysicalVolume *p_coating = new MyPhysicalVolume(0, G4ThreeVector(0, 0, 0), coatingName, l_coating,
                                                     p_layer, false, 0, checkOverlaps);

  fVolumeMap[coatingName] = p_coating;

  // 将闪烁体放入coating中央
  MyPhysicalVolume *p_scint = new MyPhysicalVolume(0, G4ThreeVector(0, 0, 0), scintName, l_scint,
                                                   p_coating, false, 0, checkOverlaps);

  fVolumeMap[scintName] = p_scint;
  // 创建光纤cladding
  G4String fiber_cladding_name = "fiber_cladding_" + std::to_string(copynumber);
  G4double fiber_length = g_lg_length; // 光纤长度，可以根据需要调整
  G4Tubs *s_fiber_cladding = new G4Tubs(
      fiber_cladding_name, 0, 0.5 * fiber_cladding_diameter, 0.5 * fiber_length, 0, 360 * deg);
  G4LogicalVolume *l_fiber_cladding = new G4LogicalVolume(
      s_fiber_cladding, s_fiberCladdingMaterial, fiber_cladding_name);

  // 设置光纤cladding的可视化属性（灰色，30%透明度）
  G4VisAttributes *fiber_cladding_vis = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.7));
  fiber_cladding_vis->SetForceSolid(true);
  l_fiber_cladding->SetVisAttributes(fiber_cladding_vis);

  // 创建光纤core
  G4String fiber_core_name = "fiber_core_" + std::to_string(copynumber);
  G4Tubs *s_fiber_core = new G4Tubs(
      fiber_core_name, 0, 0.5 * fiber_core_diameter, 0.5 * fiber_length, 0, 360 * deg);
  G4LogicalVolume *l_fiber_core = new G4LogicalVolume(
      s_fiber_core, s_fiberCoreMaterial, fiber_core_name);

  // 设置光纤core的可视化属性（黄色）
  G4VisAttributes *fiber_core_vis = new G4VisAttributes(G4Colour(0.8, 0.8, 0.0, 0.5));
  fiber_core_vis->SetForceSolid(true);
  l_fiber_core->SetVisAttributes(fiber_core_vis);

  // 将光纤core放入cladding
  new G4PVPlacement(0, G4ThreeVector(0, 0, 0), l_fiber_core, fiber_core_name,
                    l_fiber_cladding, false, copynumber, checkOverlaps);

  // 计算光纤位置
  G4ThreeVector fiber_pos = hole_pos;
  G4double fiber_offset = 0.5 * fiber_length - 0.5 * coating_thickness;

  // 根据readout_face调整光纤位置
  switch (readout_face)
  {
  case 0:
    fiber_pos += G4ThreeVector(fiber_offset, 0, 0);
    break;
  case 1:
    fiber_pos += G4ThreeVector(0, fiber_offset, 0);
    break;
  case 2:
    fiber_pos += G4ThreeVector(-fiber_offset, 0, 0);
    break;
  case 3:
    fiber_pos += G4ThreeVector(0, -fiber_offset, 0);
    break;
  }

  // 创建光纤旋转
  G4RotationMatrix *fiber_rot = new G4RotationMatrix();
  if (readout_face == 0 || readout_face == 2)
  {
    fiber_rot->rotateY(90 * deg);
  }
  else if (readout_face == 1 || readout_face == 3)
  {
    fiber_rot->rotateX(90 * deg);
  }

  // 将光纤放入coating
  new MyPhysicalVolume(fiber_rot, fiber_pos + position, fiber_cladding_name, l_fiber_cladding,
                       mother_phys, false, copynumber, checkOverlaps);

  // 创建反射层的光学表面
  new G4LogicalSkinSurface("TeflonSurface", l_coating, g_surf_Teflon);

  return p_layer;
}

// 根据输入数量和间隔生成坐标
std::vector<G4ThreeVector> generateCoordinates(int nums, double gaps)
{
  std::vector<G4ThreeVector> coordinates;

  if (nums <= 0)
  {
    return coordinates;
  }

  if (nums == 1)
  {
    coordinates.push_back(G4ThreeVector(0, 0, 0));
  }
  else if (nums == 2)
  {
    coordinates.push_back(G4ThreeVector(0, 0, -gaps / 2));
    coordinates.push_back(G4ThreeVector(0, 0, gaps / 2));
  }
  else if (nums == 3)
  {
    coordinates.push_back(G4ThreeVector(0, -gaps / 2, -sqrt(3) * gaps / 6));
    coordinates.push_back(G4ThreeVector(0, gaps / 2, -sqrt(3) * gaps / 6));
    coordinates.push_back(G4ThreeVector(0, sqrt(3) * gaps / 3, 0));
  }
  else if (nums == 4)
  {
    coordinates.push_back(G4ThreeVector(0, -gaps / 2, -gaps / 2));
    coordinates.push_back(G4ThreeVector(0, -gaps / 2, gaps / 2));
    coordinates.push_back(G4ThreeVector(0, gaps / 2, -gaps / 2));
    coordinates.push_back(G4ThreeVector(0, gaps / 2, gaps / 2));
  }
  else if (nums == 5 or nums == 6 or nums == 7)
  {
    coordinates.push_back(G4ThreeVector(0, 0, 0));
    double radius = gaps;
    double angle = 2 * M_PI / (nums - 1);
    for (int i = 0; i < (nums - 1); ++i)
    {
      double y = radius * std::cos(i * angle);
      double z = radius * std::sin(i * angle);
      coordinates.push_back(G4ThreeVector(0, y, z));
    }
  }
  else
  {
    G4Exception("CompScintSimDetectorConstruction", "op001", FatalException,
                "The number of lightguides is not supported. Supported numbers are integers from 1 to 7.");
  }

  return coordinates;
}