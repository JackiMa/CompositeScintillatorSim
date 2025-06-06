#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"

#include "MyPhysicalVolume.hh"
#include "MyTrackInfo.hh"
#include "CustomScorer.hh"
#include "utilities.hh"

// TotalEnergyScorer implementation
TotalEnergyScorer::TotalEnergyScorer(const G4String& name, G4int depth)
    : G4VPrimitiveScorer(name, depth), fHitsMap(nullptr) {}

TotalEnergyScorer::~TotalEnergyScorer() {}

void TotalEnergyScorer::Initialize(G4HCofThisEvent* HCE) {
    fHitsMap = new G4THitsMap<G4double>(GetMultiFunctionalDetector()->GetName(), GetName());
    G4int hcID = GetCollectionID(0);
    HCE->AddHitsCollection(hcID, fHitsMap);
}

G4bool TotalEnergyScorer::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    G4double edep = aStep->GetTotalEnergyDeposit();
    G4int copyNo = aStep->GetPreStepPoint()->GetTouchable()->GetVolume()->GetCopyNo();
    fHitsMap->add(copyNo, edep);
    return true;
}

void TotalEnergyScorer::EndOfEvent(G4HCofThisEvent*) {
}


// ---------------------------------- //
// ---------------------------------- //
// ---------------------------------- //


// PassingEnergyScorer implementation
PassingEnergyScorer::PassingEnergyScorer(const G4String& name,const G4String& scorer, G4int depth)
    : G4VPrimitiveScorer(name, depth),fHitsMap(nullptr),scorerName(scorer) {}

PassingEnergyScorer::~PassingEnergyScorer() {}

void PassingEnergyScorer::Initialize(G4HCofThisEvent* HCE) {
    fHitsMap = new G4THitsMap<G4double>(GetMultiFunctionalDetector()->GetName(), GetName());
    G4int hcID = GetCollectionID(0);
    HCE->AddHitsCollection(hcID, fHitsMap);
}

G4bool PassingEnergyScorer::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    // 获取 preVolume 和 postVolume
    G4VPhysicalVolume* preVolume = aStep->GetPreStepPoint()->GetTouchable()->GetVolume();
    G4VPhysicalVolume* postVolume = aStep->GetPostStepPoint()->GetTouchable()->GetVolume();

    // 获取动量方向
    G4ThreeVector momentumDirection = aStep->GetPreStepPoint()->GetMomentumDirection();
    // 检查 preVolume，动量方向是否向下（Z 轴方向 < 0），并且粒子是否离开当前体积
    if (preVolume->GetName() == scorerName && momentumDirection.z() < 0 && preVolume != postVolume) {
        G4double energy = aStep->GetPreStepPoint()->GetKineticEnergy();
        G4int copyNo = preVolume->GetCopyNo();
        fHitsMap->add(copyNo, energy);     
    }
    return true;
}

void PassingEnergyScorer::EndOfEvent(G4HCofThisEvent*) {
}


// TruelyPassingEnergyScorer implementation
TruelyPassingEnergyScorer::TruelyPassingEnergyScorer(const G4String& name,const G4String& scorer, G4int depth)
    : G4VPrimitiveScorer(name, depth),fHitsMap(nullptr),scorerName(scorer) {}

TruelyPassingEnergyScorer::~TruelyPassingEnergyScorer() {}

void TruelyPassingEnergyScorer::Initialize(G4HCofThisEvent* HCE) {
    fHitsMap = new G4THitsMap<G4double>(GetMultiFunctionalDetector()->GetName(), GetName());
    G4int hcID = GetCollectionID(0);
    HCE->AddHitsCollection(hcID, fHitsMap);
}

G4bool TruelyPassingEnergyScorer::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    // 获取 pre/post volume
    G4VPhysicalVolume* preVolume  = aStep->GetPreStepPoint()->GetTouchable()->GetVolume();
    G4VPhysicalVolume* postVolume = aStep->GetPostStepPoint()->GetTouchable()->GetVolume();

    // 安全性检查
    if(!preVolume || !postVolume) return false;

    // 获取粒子的动量方向
    G4ThreeVector momDir = aStep->GetPreStepPoint()->GetMomentumDirection();

    // 获取 Track 以及其自定义Track信息
    G4Track* theTrack = aStep->GetTrack();
    MyTrackInfo* trackInfo = dynamic_cast<MyTrackInfo*>( theTrack->GetUserInformation() );
    if(!trackInfo) {
        // 如果没有 MyTrackInfo，就无法识别是否重复统计，这里直接 return
        return false;
    }

    // 如果已经标记 "HasPassedLayer = true"，说明之前已经通过过此层，不再统计
    if(trackInfo->HasPassedLayer(scorerName)) {
        return false;
    }

    // 检查：preVolume是不是我们感兴趣的层？动量方向是不是向下 (z<0)？并且这一步要离开该体积 (preVolume != postVolume)？
    if(preVolume->GetName() == scorerName &&
       momDir.z() < 0.0 &&
       preVolume != postVolume)
    {
        G4double energy = aStep->GetPreStepPoint()->GetKineticEnergy();
        G4int copyNo = preVolume->GetCopyNo();
        fHitsMap->add(copyNo, energy);  

        // 标记本 Track“已经通过此层”
        trackInfo->SetHasPassedLayer(scorerName, true);
    }

    return true;
}

void TruelyPassingEnergyScorer::EndOfEvent(G4HCofThisEvent*) {
}


// PassingEnergyScorer_Secondary implementation
PassingEnergyScorer_Secondary::PassingEnergyScorer_Secondary(const G4String& name,const G4String& scorer, G4int depth)
    : G4VPrimitiveScorer(name, depth),fHitsMap(nullptr),scorerName(scorer) {}

PassingEnergyScorer_Secondary::~PassingEnergyScorer_Secondary() {}

void PassingEnergyScorer_Secondary::Initialize(G4HCofThisEvent* HCE) {
    fHitsMap = new G4THitsMap<G4double>(GetMultiFunctionalDetector()->GetName(), GetName());
    G4int hcID = GetCollectionID(0);
    HCE->AddHitsCollection(hcID, fHitsMap);
}

G4bool PassingEnergyScorer_Secondary::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    // 获取 preVolume 和 postVolume
    G4VPhysicalVolume* preVolume = aStep->GetPreStepPoint()->GetTouchable()->GetVolume();
    G4VPhysicalVolume* postVolume = aStep->GetPostStepPoint()->GetTouchable()->GetVolume();

    // 获取动量方向
    G4ThreeVector momentumDirection = aStep->GetPreStepPoint()->GetMomentumDirection();

    // 获取粒子的 ParentID
    G4int parentID = aStep->GetTrack()->GetParentID();

    // 检查 preVolume，动量方向是否向下（Z 轴方向 < 0），粒子是否离开当前体积，并且粒子是次级粒子
    if (preVolume->GetName() == scorerName && momentumDirection.z() < 0 && preVolume != postVolume && parentID > 0) {
        G4double energy = aStep->GetPreStepPoint()->GetKineticEnergy();
        G4int copyNo = preVolume->GetCopyNo();
        fHitsMap->add(copyNo, energy);     
    }
    return true;
}

void PassingEnergyScorer_Secondary::EndOfEvent(G4HCofThisEvent*) {
}




// TruelyPassingEnergyScorer_Secondary implementation
TruelyPassingEnergyScorer_Secondary::TruelyPassingEnergyScorer_Secondary(const G4String& name,const G4String& scorer, G4int depth)
    : G4VPrimitiveScorer(name, depth),fHitsMap(nullptr),scorerName(scorer) {}

TruelyPassingEnergyScorer_Secondary::~TruelyPassingEnergyScorer_Secondary() {}

void TruelyPassingEnergyScorer_Secondary::Initialize(G4HCofThisEvent* HCE) {
    fHitsMap = new G4THitsMap<G4double>(GetMultiFunctionalDetector()->GetName(), GetName());
    G4int hcID = GetCollectionID(0);
    HCE->AddHitsCollection(hcID, fHitsMap);
}

G4bool TruelyPassingEnergyScorer_Secondary::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    // 获取 pre/post volume
    G4VPhysicalVolume* preVolume  = aStep->GetPreStepPoint()->GetTouchable()->GetVolume();
    G4VPhysicalVolume* postVolume = aStep->GetPostStepPoint()->GetTouchable()->GetVolume();

    // 安全性检查
    if(!preVolume || !postVolume) return false;

    // 获取粒子的动量方向
    G4ThreeVector momDir = aStep->GetPreStepPoint()->GetMomentumDirection();

    // 获取粒子的 ParentID
    G4int parentID = aStep->GetTrack()->GetParentID();

    // 获取 Track 以及其自定义Track信息
    G4Track* theTrack = aStep->GetTrack();
    MyTrackInfo* trackInfo = dynamic_cast<MyTrackInfo*>( theTrack->GetUserInformation() );
    if(!trackInfo) {
        // 如果没有 MyTrackInfo，就无法识别是否重复统计，这里直接 return
        return false;
    }

    // 如果已经标记 "HasPassedLayer_secondary = true"，说明之前已经通过过此层，不再统计
    if(trackInfo->HasPassedLayer_secondary(scorerName)) {
        return false;
    }

    if(parentID <= 0) {
        // 如果不是次级粒子，直接 return
        return false;
    }

    // 检查：preVolume是不是我们感兴趣的层？动量方向是不是向下 (z<0)？并且这一步要离开该体积 (preVolume != postVolume)？
    if(preVolume->GetName() == scorerName &&
       momDir.z() < 0.0 &&
       preVolume != postVolume)
    {
        G4double energy = aStep->GetPreStepPoint()->GetKineticEnergy();
        G4int copyNo = preVolume->GetCopyNo();
        fHitsMap->add(copyNo, energy);  

        // 标记本 Track“已经通过此层”
        trackInfo->SetHasPassedLayer(scorerName, true);
    }

    return true;
}

void TruelyPassingEnergyScorer_Secondary::EndOfEvent(G4HCofThisEvent*) {
}

// ---------------------------------- //
// ---------------------------------- //
// ---------------------------------- //

// NeutronScorer implementation
NeutronScorer::NeutronScorer(const G4String& name, G4int depth)
    : G4VPrimitiveScorer(name, depth), fHitsMap(nullptr) {}

NeutronScorer::~NeutronScorer() {}

void NeutronScorer::Initialize(G4HCofThisEvent* HCE) {
    fHitsMap = new G4THitsMap<G4double>(GetMultiFunctionalDetector()->GetName(), GetName());
    G4int hcID = GetCollectionID(0);
    HCE->AddHitsCollection(hcID, fHitsMap);
}

G4bool NeutronScorer::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    G4Track* track = aStep->GetTrack();
    G4ParticleDefinition* particle = track->GetDefinition();

    // 检查是否为中子
    if (particle == G4Neutron::NeutronDefinition()) {
        // 获取轨迹的创建位置
        G4ThreeVector vertexPosition = track->GetVertexPosition();

        // 检查创建位置是否在灵敏体积内
        if (IsInsideSensitiveVolume(aStep, vertexPosition)) {
            const G4VTouchable* touchable = aStep->GetPreStepPoint()->GetTouchable();
            G4double neutronEnergy = aStep->GetPreStepPoint()->GetKineticEnergy();
            G4int copyNo = touchable->GetVolume()->GetCopyNo();
            fHitsMap->add(copyNo, neutronEnergy);
        }
    }
    return true;
}

void NeutronScorer::EndOfEvent(G4HCofThisEvent*) {
}




// ---------------------------------- //
// ---------------------------------- //
// ---------------------------------- //

ElectronEnergyScorer::ElectronEnergyScorer(const G4String& name, G4int depth)
    : G4VPrimitiveScorer(name, depth), fHitsMap(nullptr) {}

ElectronEnergyScorer::~ElectronEnergyScorer() {}

void ElectronEnergyScorer::Initialize(G4HCofThisEvent* HCE) {
    fHitsMap = new G4THitsMap<G4double>(GetMultiFunctionalDetector()->GetName(), GetName());
    G4int hcID = GetCollectionID(0);
    HCE->AddHitsCollection(hcID, fHitsMap);
}

G4bool ElectronEnergyScorer::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    G4Track* track = aStep->GetTrack();
    G4ParticleDefinition* particle = track->GetDefinition();

    // 检查是否为电子
    if (particle == G4Electron::ElectronDefinition()) {
        // 获取轨迹的创建位置
        G4ThreeVector vertexPosition = track->GetVertexPosition();

        // 检查创建位置是否在灵敏体积内
        if (IsInsideSensitiveVolume(aStep, vertexPosition)) {
            G4double electronEnergy = aStep->GetPreStepPoint()->GetKineticEnergy();
            const G4VTouchable* touchable = aStep->GetPreStepPoint()->GetTouchable();
            G4int copyNo = touchable->GetVolume()->GetCopyNo();
            fHitsMap->add(copyNo, electronEnergy);
        }
    }
    return true;
}


void ElectronEnergyScorer::EndOfEvent(G4HCofThisEvent*) {
}


// ---------------------------------- //
// ---------------------------------- //
// ---------------------------------- //

HEPhotonScorer::HEPhotonScorer(const G4String& name, G4int depth)
    : G4VPrimitiveScorer(name, depth), fHitsMap(nullptr) {}

HEPhotonScorer::~HEPhotonScorer() {
    delete fHitsMap;
}

void HEPhotonScorer::Initialize(G4HCofThisEvent* HCE) {
    fHitsMap = new G4THitsMap<G4double>(GetMultiFunctionalDetector()->GetName(), GetName());
    G4int hcID = GetCollectionID(0);
    HCE->AddHitsCollection(hcID, fHitsMap);
}

G4bool HEPhotonScorer::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    G4Track* track = aStep->GetTrack();
    G4ParticleDefinition* particle = track->GetDefinition();

    // 检查是否为光子
    if (particle == G4Gamma::GammaDefinition()) {
        // 获取轨迹的创建位置
        G4ThreeVector vertexPosition = track->GetVertexPosition();

        // 判断创建位置是否在灵敏体积内
        if (IsInsideSensitiveVolume(aStep, vertexPosition)) {
            G4double photonEnergy = aStep->GetPreStepPoint()->GetKineticEnergy();
            // 只统计能量大于1keV的光子
            if (photonEnergy > 1 * CLHEP::keV) {
                const G4VTouchable* touchable = aStep->GetPreStepPoint()->GetTouchable();
                G4int copyNo = touchable->GetVolume()->GetCopyNo();
                fHitsMap->add(copyNo, photonEnergy);
            }
        }
    }
    return true;
}

void HEPhotonScorer::EndOfEvent(G4HCofThisEvent*) {
}

// ---------------------------------- //
// ---------------------------------- //
// ---------------------------------- //

SCLightScorer::SCLightScorer(const G4String& name, const G4int fillH1Id, G4int depth)
    : G4VPrimitiveScorer(name, depth),fHistogramId(fillH1Id){}
SCLightScorer::~SCLightScorer() {}

G4bool SCLightScorer::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    G4Track* aTrack = aStep->GetTrack();
    // 确保只处理光子并且产生过程是闪烁
    if (aTrack->GetDefinition() == G4OpticalPhoton::Definition() &&
        aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation") {
        G4int trackID = aTrack->GetTrackID();
        // 检查光子是否已经处理过
        if (processedTrackIDs.find(trackID) == processedTrackIDs.end()) {
            G4double energy = aTrack->GetTotalEnergy();
            G4double wavelength = (1239.841939 * nm) / energy;  // 将能量转换为波长
            auto analysisManager = G4AnalysisManager::Instance();
            analysisManager->FillH1(fHistogramId, wavelength);
            // 标记光子为已处理
            processedTrackIDs.insert(trackID);
        }
    }
    return true;
}

void SCLightScorer::Initialize(G4HCofThisEvent*) {
}

void SCLightScorer::EndOfEvent(G4HCofThisEvent*) {
    processedTrackIDs.clear();
}

// ---------------------------------- //
// ---------------------------------- //
// ---------------------------------- //
CherenkovLightScorer::CherenkovLightScorer(const G4String& name, const G4int fillH1Id, G4int depth)
    : G4VPrimitiveScorer(name, depth),fHistogramId(fillH1Id){}
CherenkovLightScorer::~CherenkovLightScorer() {}

G4bool CherenkovLightScorer::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    G4Track* aTrack = aStep->GetTrack();
    // 确保只处理光子并且是切伦科夫光子
    if (aTrack->GetDefinition() == G4OpticalPhoton::Definition() &&
        aTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov") {
        G4int trackID = aTrack->GetTrackID();
        // 检查光子是否已经处理过
        if (processedTrackIDs.find(trackID) == processedTrackIDs.end()) {
            G4double energy = aTrack->GetTotalEnergy();
            G4double wavelength = (1239.841939 * nm) / energy;  // 将能量转换为波长
            auto analysisManager = G4AnalysisManager::Instance();
            analysisManager->FillH1(fHistogramId, wavelength);
            // 标记光子为已处理
            processedTrackIDs.insert(trackID);
        }
    }
    return true;
}

void CherenkovLightScorer::Initialize(G4HCofThisEvent*) {
}

void CherenkovLightScorer::EndOfEvent(G4HCofThisEvent*) {
    processedTrackIDs.clear();
}

// ---------------------------------- //
// ---------------------------------- //
// ---------------------------------- //

FiberAcceptanceScorer::FiberAcceptanceScorer(const G4String& name, const G4int fillH1Id, G4int depth)
    : G4VPrimitiveScorer(name, depth), fHistogramId(fillH1Id) {}

FiberAcceptanceScorer::~FiberAcceptanceScorer() {}

G4bool FiberAcceptanceScorer::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    G4Track* aTrack = aStep->GetTrack();
    // G4cout << "PreStepPoint: " << aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName() << ", " << aStep->GetPreStepPoint()->GetMaterial()->GetName() << G4endl;
    // G4cout << "PostStepPoint: " << aStep->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName() << ", " << aStep->GetPostStepPoint()->GetMaterial()->GetName() << G4endl;
            
    if (aTrack->GetDefinition() == G4OpticalPhoton::Definition()) {
        G4int trackID = aTrack->GetTrackID();
        // 检查光子是否已经处理过
        if (processedTrackIDs.find(trackID) == processedTrackIDs.end()) {
            G4double energy = aTrack->GetTotalEnergy();
            G4double wavelength = (1239.841939 * nm) / energy;  // 将能量转换为波长

            // 获取折射率
            // G4cout 一下想要获取折射率的两个几何体的名称和材料名称包括注释

            G4MaterialPropertyVector* rindexVector1 = aStep->GetPreStepPoint()->GetMaterial()->GetMaterialPropertiesTable()->GetProperty("RINDEX");
            G4MaterialPropertyVector* rindexVector2 = aStep->GetPostStepPoint()->GetMaterial()->GetMaterialPropertiesTable()->GetProperty("RINDEX");

            G4double n1 = rindexVector1->Value(energy);
            G4double n2 = rindexVector2->Value(energy);

            G4ThreeVector photonDirection = aTrack->GetMomentumDirection();
            G4ThreeVector normal = aStep->GetPreStepPoint()->GetTouchableHandle()->GetSolid()->SurfaceNormal(aStep->GetPreStepPoint()->GetPosition());

            // 计算入射角的余弦
            G4double cosTheta = -photonDirection.dot(normal);
            
            // 根据折射率计算极限角
            G4double criticalAngle = std::asin(n2 / n1);

            // 如果光子从低折射率介质进入高折射率介质
            // G4cout << "n1: " << n1 << ", n2: " << n2 << ", cosTheta: " << cosTheta << ", Angle: " << std::acos(cosTheta) / deg << G4endl;
            if (n1 < n2 && std::acos(cosTheta) < criticalAngle) {
            // G4cout << "Photon ID: " << trackID << " is accepted" << G4endl;

                auto analysisManager = G4AnalysisManager::Instance();
                analysisManager->FillH1(fHistogramId, wavelength);
                // 标记光子为已处理
                processedTrackIDs.insert(trackID);
            }
        }
    }
    return true;
}

void FiberAcceptanceScorer::Initialize(G4HCofThisEvent*) {
    // 初始化代码
}

void FiberAcceptanceScorer::EndOfEvent(G4HCofThisEvent*) {
    processedTrackIDs.clear();
}

// ---------------------------------- //
// ---------------------------------- //
// ---------------------------------- //

FiberEntryPhotonScorer::FiberEntryPhotonScorer(const G4String& name, const G4int fillH1Id, G4int depth)
    : G4VPrimitiveScorer(name, depth), fHistogramId(fillH1Id) {}

FiberEntryPhotonScorer::~FiberEntryPhotonScorer() {}

G4bool FiberEntryPhotonScorer::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    G4Track* aTrack = aStep->GetTrack();

    if (aTrack->GetDefinition() == G4OpticalPhoton::Definition()) {
        G4int trackID = aTrack->GetTrackID();
        // 检查光子是否已经处理过
        if (processedTrackIDs.find(trackID) == processedTrackIDs.end()) {
            G4double energy = aTrack->GetTotalEnergy();
            G4double wavelength = (1239.841939 * nm) / energy;  // 将能量转换为波长

            // 记录进入光纤的光谱
            auto analysisManager = G4AnalysisManager::Instance();
            analysisManager->FillH1(fHistogramId, wavelength);
            // 标记光子为已处理
            processedTrackIDs.insert(trackID);
        }
    }
    return true;
}

void FiberEntryPhotonScorer::EndOfEvent(G4HCofThisEvent*) {
    processedTrackIDs.clear();
}

// ---------------------------------- //
// ---------------------------------- //
// ---------------------------------- //

// 判断创建位置是否在灵敏体积内
G4bool IsInsideSensitiveVolume(G4Step* aStep, const G4ThreeVector& vertexPosition) {
    // 获取物理体积的变换矩阵
    const G4VTouchable* touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4VPhysicalVolume* volume = touchable->GetVolume();
    G4AffineTransform transform = touchable->GetHistory()->GetTopTransform();

    // 将点的坐标转换到逻辑体的本地坐标系
    G4ThreeVector localPosition = transform.TransformPoint(vertexPosition);

    // 检查创建位置是否在灵敏体积内
    return volume->GetLogicalVolume()->GetSolid()->Inside(localPosition) == kInside;
}