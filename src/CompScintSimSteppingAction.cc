//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file CompScintSimSteppingAction.cc
/// \brief Implementation of the CompScintSimSteppingAction class

#include "CompScintSimSteppingAction.hh"
#include "CompScintSimRun.hh"
#include "CompScintSimEventAction.hh"

#include "G4Event.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4OpticalPhoton.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include <vector>
#include <sstream>

#include "config.hh"
#include "ScintillatorLayerManager.hh"
#include "MyTrackInfo.hh"
#include "utilities.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CompScintSimSteppingAction::CompScintSimSteppingAction(CompScintSimEventAction *event)
    : G4UserSteppingAction(), fEventAction(event)
{
    // 初始化ScintillatorLayerManager（如果尚未初始化）
    if (!ScintillatorLayerManager::GetInstance().IsInitialized()) {
        ScintillatorLayerManager::GetInstance().Initialize(g_ScintillatorGeometry);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
CompScintSimSteppingAction::~CompScintSimSteppingAction() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void CompScintSimSteppingAction::UserSteppingAction(const G4Step *step)
{
    // 获取当前步骤的所有基本信息
    G4Track* track = step->GetTrack();
    G4StepPoint* preStepPoint = step->GetPreStepPoint();
    G4StepPoint* postStepPoint = step->GetPostStepPoint();
    
    if (!preStepPoint || !postStepPoint) return;
    
    // 获取步骤中的能量沉积
    G4double edep = step->GetTotalEnergyDeposit();
    
    // 如果没有能量沉积，不做处理
    if (edep <= 0) return;
    
    // 获取当前体积
    G4VPhysicalVolume* volume = preStepPoint->GetTouchableHandle()->GetVolume();
    if (!volume) return;
    
    // 获取体积名称
    G4String volumeName = volume->GetName();
    
    // 检查是否在闪烁体层中
    if (volumeName.find("scint_layer_") != G4String::npos) {
        // 从名称中提取层ID
        G4String layerIDStr = volumeName.substr(12); // 去除"scint_layer_"前缀
        G4int layerID = std::stoi(layerIDStr);
        
        // 将能量沉积添加到EventAction
        if (fEventAction) {
            fEventAction->AddEnergyDeposit(layerID, edep);
        }
    }
    
    // ----------------------------------------------------
    // 对次级粒子进行标记，判断是否已经穿越某层SD
    // ----------------------------------------------------
    // 母粒子 track
    MyTrackInfo *parentInfo = dynamic_cast<MyTrackInfo *>(track->GetUserInformation());

    // 获取次级粒子列表
    const std::vector<const G4Track *> *secondaries = step->GetSecondaryInCurrentStep();
    if (secondaries && !secondaries->empty())
    {
        // 遍历所有次级粒子
        for (size_t i = 0; i < secondaries->size(); i++)
        {
            G4Track *childTrack = const_cast<G4Track *>((*secondaries)[i]);
            if (!childTrack)
                continue;

            // 为次级粒子分配新的 MyTrackInfo
            MyTrackInfo *childInfo = new MyTrackInfo();
            // 如果母粒子有标记，则继承
            if (parentInfo)
            {
                childInfo->InheritPassedLayers(parentInfo);
                childInfo->InheritPassedLayers_secondary(parentInfo);
            }

            // 将 trackInfo 附加到二次粒子
            childTrack->SetUserInformation(childInfo);
        }
    }
    
    // 光子处理
    // 判断是否是光子
    static const G4ParticleDefinition *opticalphoton = G4OpticalPhoton::OpticalPhotonDefinition();
    const G4ParticleDefinition *particleDef = track->GetParticleDefinition();
    
    if (particleDef != opticalphoton) return;
    
    // 判断是否跨越几何边界
    if (postStepPoint->GetStepStatus() != fGeomBoundary) return;

    G4int trackID = track->GetTrackID();
    
    // 检查该光子是否已经处理过
    if (fEventAction->processedTrackIDs.find(trackID) != fEventAction->processedTrackIDs.end()) {
        return;
    }
    
    // 获取前后点的逻辑体积
    G4VPhysicalVolume *preVolume = preStepPoint->GetPhysicalVolume();
    G4VPhysicalVolume *postVolume = postStepPoint->GetPhysicalVolume();
    if (!preVolume || !postVolume) return;
    
    G4String preVolumeName = preVolume->GetLogicalVolume()->GetName();
    G4String postVolumeName = postVolume->GetLogicalVolume()->GetName();
    
    // 判断是否从晶体或世界体进入到光纤芯
    bool isEnteringFiberCore = (postVolumeName.find("fiber_core") != G4String::npos);
    bool isFromCrystalOrWorld = (preVolumeName == "World" || 
                               preVolumeName.find("scint_layer_") != G4String::npos);
    
    // 如果不是从晶体或世界体进入光纤芯，则跳过
    if (!isEnteringFiberCore || !isFromCrystalOrWorld) {
        return;
    }
    
    // 从光纤芯获取层号（copynumber）
    G4int layerCopyNo = postVolume->GetCopyNo();
    
    // 添加对layerCopyNo为0的情况的详细调试
    if (layerCopyNo == 0) {
        myPrint(ERROR, f("【光子跟踪】ID: %d, 发现copynumber为0的光纤芯体积: %s", trackID, postVolumeName.c_str()));
        return;
    }
    
    // 获取该层的readout_face
    const ScintillatorLayerInfo* layerInfo = ScintillatorLayerManager::GetInstance().GetLayerInfo(layerCopyNo);
    if (!layerInfo) {
        myPrint(ERROR, f("【光子跟踪】ID: %d, 无法获取层%d的信息", trackID, layerCopyNo));
        return;
    }
    
    // 获取光子能量和波长
    G4double energy = track->GetTotalEnergy();
    // 将能量转换为波长，并直接计算纳米值
    G4double wavelengthNm = (1239.841939) / (energy/eV);
    
    // 计算光子方向与光纤端面方向的夹角
    G4ThreeVector photonDirection = track->GetMomentumDirection();
    
    // 获取光子进入点的坐标
    G4ThreeVector enterPosition = postStepPoint->GetPosition();
    
    // 获取光纤芯的固体对象和变换
    G4TouchableHandle touchable = postStepPoint->GetTouchableHandle();
    G4VSolid* fiberCoreSolid = touchable->GetSolid();
    
    // 将全局坐标转换为本地坐标系下的位置
    G4ThreeVector localPosition = touchable->GetHistory()->GetTopTransform().TransformPoint(enterPosition);
    
    // 获取该点的表面法线（在本地坐标系中）
    G4ThreeVector localNormal = fiberCoreSolid->SurfaceNormal(localPosition);
    
    // 将法线从本地坐标系转回全局坐标系
    G4ThreeVector fiberNormal = touchable->GetHistory()->GetTopTransform().TransformAxis(localNormal);
    
    // 由于我们关心的是光子是否从端面进入光纤，需要确保法线方向正确
    // 检查自动获取的法线是否与readout_face定义的方向一致
    G4ThreeVector expectedNormal;
    switch (layerInfo->readout_face) {
        case 0: // +X面
            expectedNormal = G4ThreeVector(1.0, 0.0, 0.0);
            break;
        case 1: // +Y面
            expectedNormal = G4ThreeVector(0.0, 1.0, 0.0);
            break;
        case 2: // -X面
            expectedNormal = G4ThreeVector(-1.0, 0.0, 0.0);
            break;
        case 3: // -Y面
            expectedNormal = G4ThreeVector(0.0, -1.0, 0.0);
            break;
        default:
            myPrint(ERROR, f("【光子跟踪】ID: %d, 警告: 无效的readout_face值: %d", 
                trackID, layerInfo->readout_face));
            return;
    }
    
    // 检查自动获取的法线与预期方向是否几乎重合
    G4double dotProduct = fiberNormal.dot(expectedNormal);
    G4double angle = std::acos(std::abs(dotProduct)) / deg;
    
    if (std::abs(dotProduct) < 0.99) { 
        return; 
    }
    
    // 如果法线方向与预期相反，不处理
    if (dotProduct < 0) {
        return;
    }
    
    // 计算入射角的余弦值
    G4double cosTheta = -photonDirection.dot(fiberNormal);
    // 如果光子方向与法线方向的点积为负，说明光子是从后面进入光纤的，跳过
    if (cosTheta <= 0) {
        return;
    }
    
    G4double theta = std::acos(cosTheta);
    
    // 使用全局配置的NA值判断能否进入
    // 计算临界角
    G4double criticalAngle;
    if (g_lg_na <= 0 || g_lg_na >= 1) {
        // 如果NA值无效，直接报错
        G4ExceptionDescription ed;
        ed << "Invalid NA value: " << g_lg_na << ". NA must be between 0 and 1.";
        G4Exception("CompScintSimSteppingAction::UserSteppingAction", 
                  "InvalidNA", FatalException, ed);
    }
    
    criticalAngle = std::asin(g_lg_na);
    
    // 8. 判断是否满足NA条件
    if (theta < criticalAngle) {
        // 记录已处理过的光子ID
        fEventAction->processedTrackIDs.insert(trackID);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
