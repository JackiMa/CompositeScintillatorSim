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

#include "G4Event.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4OpticalPhoton.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4AnalysisManager.hh"
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
    // ----------------------------------------------------
    // 对次级粒子进行标记，判断是否已经穿越某层SD
    // ----------------------------------------------------
    // 母粒子 track
    G4Track *theTrack = step->GetTrack();
    MyTrackInfo *parentInfo = dynamic_cast<MyTrackInfo *>(theTrack->GetUserInformation());

    // 获取次级粒子列表
    const std::vector<const G4Track *> *secondaries = step->GetSecondaryInCurrentStep();
    if (!secondaries || secondaries->empty())
    {
    }
    else
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

    // ----------------------------------------------------
    // 上面是对次级粒子进行标记，判断是否已经穿越某层SD的代码
    // ----------------------------------------------------

    // 测试逻辑: 添加测试数据到直方图中
    if (g_debug_mode) {
        myPrint(DEBUG, "开始添加测试数据到NA直方图中");
        // 获取分析管理器
        auto analysisManager = G4AnalysisManager::Instance();
        
        // 计算250nm对应的能量 (eV) = 1239.841939 / 波长(nm)
        G4double testWavelengthNm = 250.0;  // 直接使用nm作为单位

        
        myPrint(DEBUG, f("测试波长: %f nm", testWavelengthNm));
        
        // 为每一层添加100个特定波长的光子数据
        G4int numLayers = ScintillatorLayerManager::GetInstance().GetCopynumbers().size();
        for (G4int i = 1; i <= numLayers; i++) {
            G4String histName = "Layer_" + std::to_string(i) + "_FiberNA";
            G4int histId = analysisManager->GetH1Id(histName);
            
            if (histId >= 0) {
                for (G4int j = 0; j < 100; j++) {
                    // 直接用波长nm值填充直方图
                    analysisManager->FillH1(histId, testWavelengthNm);
                }
                myPrint(DEBUG, f("已向层%d的NA直方图添加100个波长为%f nm 的测试光子", 
                              i, testWavelengthNm));
            } else {
                myPrint(ERROR, f("无法找到层%d的NA直方图", i));
            }
        }
        myPrint(DEBUG, "测试数据添加完成");
    }

    // 1. 首先判断是否是光子
    static const G4ParticleDefinition *opticalphoton = G4OpticalPhoton::OpticalPhotonDefinition();
    const G4ParticleDefinition *particleDef = step->GetTrack()->GetParticleDefinition();
    
    if (particleDef != opticalphoton) return;
    
    // 获取步骤的前后点及其物理体积名称
    G4StepPoint *preStepPoint = step->GetPreStepPoint();
    G4StepPoint *postStepPoint = step->GetPostStepPoint();
    if (!preStepPoint || !postStepPoint) return;
    
    // 判断是否跨越几何边界
    if (postStepPoint->GetStepStatus() != fGeomBoundary) return;

    G4Track *track = step->GetTrack();
    G4int trackID = track->GetTrackID();
    
    // 调试信息: 输出光子基本信息
    if (g_debug_mode) {
    if (trackID % 100 == 0) { // 每100个光子输出一次
        G4double energy = track->GetTotalEnergy();
        G4double wavelength = (1239.841939 * nm) / (energy/eV);
        myPrint(DEBUG, f("【光子跟踪】ID: %d, 能量: %f eV, 波长: %f nm, 动量方向: (%f, %f, %f)",
            trackID, 
            energy/eV,
            wavelength/nm,
            track->GetMomentumDirection().x(),
                track->GetMomentumDirection().y(),
                track->GetMomentumDirection().z()));
        }
    }
    
    // 检查该光子是否已经处理过
    if (fEventAction->processedTrackIDs.find(trackID) != fEventAction->processedTrackIDs.end()) {
        myPrint(DEBUG, f("【光子跟踪】ID: %d 已处理过，跳过", trackID));
        return;
    }
    
    // 获取前后点的逻辑体积
    G4VPhysicalVolume *preVolume = preStepPoint->GetPhysicalVolume();
    G4VPhysicalVolume *postVolume = postStepPoint->GetPhysicalVolume();
    if (!preVolume || !postVolume) return;
    
    G4String preVolumeName = preVolume->GetLogicalVolume()->GetName();
    G4String postVolumeName = postVolume->GetLogicalVolume()->GetName();
    
    // 调试信息: 输出体积信息
    myPrint(DEBUG, f("【光子跟踪】ID: %d, 从 %s 进入 %s", 
        trackID, preVolumeName.c_str(), postVolumeName.c_str()));
    
    // 2. 判断是否从晶体或世界体进入到光纤芯
    // 检查是否进入光纤芯（只考虑进入fiber_core_id的光子）
    bool isEnteringFiberCore = (postVolumeName.find("fiber_core") != G4String::npos);
    
    bool isFromCrystalOrWorld = (preVolumeName == "World" || 
                               preVolumeName.find("scint_layer_") != G4String::npos);
    
    // 如果不是从晶体或世界体进入光纤芯，则跳过
    if (!isEnteringFiberCore || !isFromCrystalOrWorld) {
        myPrint(DEBUG, f("【光子跟踪】ID: %d, 不是从晶体或世界体进入光纤芯，跳过", trackID));
        return;
    }
    
    // 3. 直接从光纤芯获取层号（copynumber）
    G4int layerCopyNo = postVolume->GetCopyNo();
    myPrint(DEBUG, f("【光子跟踪】ID: %d, 进入光纤芯，层号: %d", trackID, layerCopyNo));
    
    // 添加对layerCopyNo为0的情况的详细调试
    if (layerCopyNo == 0) {
        myPrint(ERROR, f("【光子跟踪】ID: %d, 发现copynumber为0的光纤芯体积: %s", trackID, postVolumeName.c_str()));
        
        // 输出光子位置信息
        G4ThreeVector position = postStepPoint->GetPosition();
        myPrint(ERROR, f("光子位置: (%f, %f, %f) mm", position.x()/mm, position.y()/mm, position.z()/mm));
        
        // 输出完整的触摸历史以跟踪体积层次结构
        G4TouchableHandle touchable = postStepPoint->GetTouchableHandle();
        myPrint(ERROR, f("触摸历史深度: %d", touchable->GetHistoryDepth()));
        for (G4int i = 0; i < touchable->GetHistoryDepth(); i++) {
            myPrint(ERROR, f("层次 %d: 体积 %s, copynumber %d", 
                i, touchable->GetVolume(i)->GetName().c_str(), touchable->GetCopyNumber(i)));
        }
        
        // 继续处理，但跳过该光子
        return;
    }
    
    // 4. 获取该层的readout_face
    const ScintillatorLayerInfo* layerInfo = ScintillatorLayerManager::GetInstance().GetLayerInfo(layerCopyNo);
    if (!layerInfo) {
        myPrint(ERROR, f("【光子跟踪】ID: %d, 无法获取层%d的信息", trackID, layerCopyNo));
        return;
    }
    
    myPrint(DEBUG, f("【光子跟踪】ID: %d, 层%d的readout_face为: %d", 
        trackID, layerCopyNo, layerInfo->readout_face));
    
    // 5. 获取光子能量和波长
    G4double energy = track->GetTotalEnergy();
    // 将能量转换为波长，并直接计算纳米值
    G4double wavelengthNm = (1239.841939) / (energy/eV);
    
    myPrint(DEBUG, f("【光子跟踪】ID: %d, 能量: %f eV, 波长: %f nm", 
                     trackID, energy/eV, wavelengthNm));
    
    // 6. 计算光子方向与光纤端面方向的夹角
    G4ThreeVector photonDirection = track->GetMomentumDirection();
    
    // 使用Geant4 API获取表面法线向量
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
    // 注意：这是必要的，因为光子方向是在全局坐标系中定义的
    // 而SurfaceNormal返回的是固体本地坐标系中的法线
    G4ThreeVector fiberNormal = touchable->GetHistory()->GetTopTransform().TransformAxis(localNormal);
    
    // 调试信息: 输出法线信息
    myPrint(DEBUG, f("【光子跟踪】ID: %d, 进入点: (%f, %f, %f) mm", 
        trackID, 
        enterPosition.x()/mm, 
        enterPosition.y()/mm, 
        enterPosition.z()/mm));
        
    myPrint(DEBUG, f("【光子跟踪】ID: %d, 本地坐标: (%f, %f, %f) mm", 
        trackID, 
        localPosition.x()/mm, 
        localPosition.y()/mm, 
        localPosition.z()/mm));
        
    myPrint(DEBUG, f("【光子跟踪】ID: %d, 本地法线: (%f, %f, %f)", 
        trackID, 
        localNormal.x(), 
        localNormal.y(), 
        localNormal.z()));
        
    myPrint(DEBUG, f("【光子跟踪】ID: %d, 全局法线: (%f, %f, %f)", 
        trackID, 
        fiberNormal.x(), 
        fiberNormal.y(), 
        fiberNormal.z()));
    
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
    
    myPrint(DEBUG, f("【光子跟踪】ID: %d, 期望法线: (%f, %f, %f)", 
        trackID, 
        expectedNormal.x(), 
        expectedNormal.y(), 
        expectedNormal.z()));
    
    // 检查自动获取的法线与预期方向是否几乎重合
    // 由于几何构建时确保readout_face与坐标轴平行，应该几乎完全重合
    G4double dotProduct = fiberNormal.dot(expectedNormal);
    G4double angle = std::acos(std::abs(dotProduct)) / deg;
    
    myPrint(DEBUG, f("【光子跟踪】ID: %d, 法线点积: %f, 夹角: %f 度", 
        trackID, dotProduct, angle));
    
    if (std::abs(dotProduct) < 0.99) { // 要求夹角小于约8度
        myPrint(ERROR, f("警告: 自动获取的法线与预期方向不重合!"));
        myPrint(ERROR, f("自动法线: (%f, %f, %f), 预期法线: (%f, %f, %f)", 
                         fiberNormal.x(), fiberNormal.y(), fiberNormal.z(),
                         expectedNormal.x(), expectedNormal.y(), expectedNormal.z()));
        myPrint(ERROR, f("点积值: %f, 夹角: %f 度", 
                         dotProduct, std::acos(std::abs(dotProduct))/deg));
        myPrint(ERROR, f("层ID: %d, readout_face: %d", 
                         layerCopyNo, layerInfo->readout_face));
        
        // 详细调试信息
        myPrint(DEBUG, f("光子位置: (%f, %f, %f)", 
                       enterPosition.x(), enterPosition.y(), enterPosition.z()));
        myPrint(DEBUG, f("本地坐标: (%f, %f, %f)", 
                       localPosition.x(), localPosition.y(), localPosition.z()));
        myPrint(DEBUG, f("本地法线: (%f, %f, %f)", 
                       localNormal.x(), localNormal.y(), localNormal.z()));
        
        // 这可能表明几何定义有问题
        return; 
    }
    
    // 如果法线方向与预期相反，经实际检测法线是光子已经从光纤另一端离开了，不用管
    if (dotProduct < 0) {
        if(g_debug_mode) {
        myPrint(ERROR, f("法线方向与预期相反!"));
        myPrint(ERROR, f("光子位置: (%f, %f, %f)", 
                      enterPosition.x(), enterPosition.y(), enterPosition.z()));
        myPrint(ERROR, f("本地坐标: (%f, %f, %f)", 
                      localPosition.x(), localPosition.y(), localPosition.z()));
        myPrint(ERROR, f("本地法线: (%f, %f, %f)", 
                      localNormal.x(), localNormal.y(), localNormal.z()));
        myPrint(ERROR, f("全局法线: (%f, %f, %f), 预期法线: (%f, %f, %f)", 
                      fiberNormal.x(), fiberNormal.y(), fiberNormal.z(),
                      expectedNormal.x(), expectedNormal.y(), expectedNormal.z()));
        
        // 输出分隔行
        myPrint(INFO, f("=========================================="));
        myPrint(INFO, f("发现法线方向与预期相反！位置: (%f, %f, %f)", 
                      enterPosition.x()/mm, enterPosition.y()/mm, enterPosition.z()/mm));
        
        // 创建一个完整的命令字符串，方便用户一键复制
        std::stringstream cmdStream;
        
        // 保留必要的小数位数，避免过长的数字
        cmdStream.precision(5);
        cmdStream.setf(std::ios::fixed, std::ios::floatfield);
        
        // 坐标转换 - 从mm到m (Geant4GUI默认单位)
        G4double xPos = enterPosition.x()/mm/1000.0;
        G4double yPos = enterPosition.y()/mm/1000.0;
        G4double zPos = enterPosition.z()/mm/1000.0;
        
        // 箭头长度(0.01m = 1cm)
        G4double arrowLength = 0.01;
        
        // 准备可视化命令 - 所有坐标单位为m
        // 添加实际法线箭头
        cmdStream << "/vis/scene/add/arrow "
            << xPos << " " 
            << yPos << " " 
            << zPos << " " 
            << fiberNormal.x()*arrowLength << " " 
            << fiberNormal.y()*arrowLength << " " 
            << fiberNormal.z()*arrowLength << std::endl;
            
        // 添加预期法线箭头
        cmdStream << "/vis/scene/add/arrow "
            << xPos << " " 
            << yPos << " " 
            << zPos << " " 
            << expectedNormal.x()*arrowLength << " " 
            << expectedNormal.y()*arrowLength << " " 
            << expectedNormal.z()*arrowLength << std::endl;
            
        // 添加光子方向箭头
        cmdStream << "/vis/scene/add/arrow "
            << xPos << " " 
            << yPos << " " 
            << zPos << " " 
            << photonDirection.x()*arrowLength << " " 
            << photonDirection.y()*arrowLength << " " 
            << photonDirection.z()*arrowLength;
        
        // 获取完整的命令字符串
        std::string allCommands = cmdStream.str();
        
        myPrint(INFO, f("Copy all commands below to execute in Geant4 GUI:"));
        // 直接输出完整命令，不带INFO前缀
        std::cout << "-------------------------------------------------------------------" << std::endl;
        std::cout << allCommands << std::endl;
        std::cout << "-------------------------------------------------------------------" << std::endl;
        std::cout << "Arrow 1: Actual Normal, Arrow 2: Expected Normal, Arrow 3: Photon Direction" << std::endl;
        std::cout << "All coordinates in meters (Geant4 default unit)" << std::endl;
        
        // 输出更多调试信息以帮助诊断
        myPrint(ERROR, f("光子来自体积: %s, 进入体积: %s", 
                      preVolumeName.c_str(), postVolumeName.c_str()));
        myPrint(ERROR, f("光子动量方向: (%f, %f, %f)", 
                      photonDirection.x(), photonDirection.y(), photonDirection.z()));
        return;
        }
        // 直接返回
        return;
    }
    
    // 计算入射角的余弦值
    G4double cosTheta = -photonDirection.dot(fiberNormal);
    // 如果光子方向与法线方向的点积为负，说明光子是从后面进入光纤的，跳过
    if (cosTheta <= 0) {
        myPrint(DEBUG, f("【光子跟踪】ID: %d, 光子从光纤背面进入 (cosTheta = %f)，跳过", 
            trackID, cosTheta));
        return;
    }
    
    G4double theta = std::acos(cosTheta);
    myPrint(DEBUG, f("【光子跟踪】ID: %d, 入射角: %f 度", trackID, theta/deg));
    
    // 7. 使用全局配置的NA值判断能否进入
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
    myPrint(DEBUG, f("【光子跟踪】ID: %d, 使用配置NA值: %f, 临界角: %f 度", 
            trackID, g_lg_na, criticalAngle/deg));
    
    // 8. 判断是否满足NA条件
    if (theta < criticalAngle) {
        myPrint(DEBUG, f("【光子跟踪】ID: %d, 满足NA条件 (入射角 %f < 临界角 %f)", 
            trackID, theta/deg, criticalAngle/deg));
            
        // 获取分析管理器
        auto analysisManager = G4AnalysisManager::Instance();
        
        // 为该层对应的光子波长直方图添加数据
        G4String histName = "Layer_" + std::to_string(layerCopyNo) + "_FiberNA";
        G4int histId = analysisManager->GetH1Id(histName);
        
        if (histId >= 0) {
            // 直接用纳米波长值填充直方图
            analysisManager->FillH1(histId, wavelengthNm);
            
            // 记录已处理过的光子ID
            fEventAction->processedTrackIDs.insert(trackID);
            
            // 输出调试信息
            myPrint(INFO, f("光子ID: %d 能量: %f eV (波长: %f nm) 入射角: %f 度 进入层 %d 的光纤芯，满足NA条件", 
                      trackID, energy/eV, wavelengthNm, theta/deg, layerCopyNo));
        } else {
            myPrint(ERROR, f("【光子跟踪】ID: %d, 无法找到层%d的光子波长直方图", 
                trackID, layerCopyNo));
        }
    } else {
        myPrint(DEBUG, f("【光子跟踪】ID: %d, 不满足NA条件 (入射角 %f > 临界角 %f), 跳过", 
            trackID, theta/deg, criticalAngle/deg));
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
