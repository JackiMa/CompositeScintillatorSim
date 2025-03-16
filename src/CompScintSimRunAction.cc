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
/// \file CompScintSim/src/CompScintSimRunAction.cc
/// \brief Implementation of the CompScintSimRunAction class
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "CompScintSimRunAction.hh"
#include "CompScintSimPrimaryGeneratorAction.hh"
#include "CompScintSimRun.hh"
#include "G4ParticleDefinition.hh"
#include "G4Run.hh"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <mutex>
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "G4AnalysisManager.hh"
#include "G4AccumulableManager.hh"
#include "G4SDManager.hh"

// 添加ROOT头文件
#include "tools/wroot/file"
#include "tools/wroot/directory"

#include "CompScintSimRunActionMessenger.hh"

#include "config.hh"
#include "ScintillatorLayerManager.hh"

#include <chrono>
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
CompScintSimRunAction::CompScintSimRunAction(CompScintSimPrimaryGeneratorAction *prim)
    : G4UserRunAction(), fRun(nullptr), fPrimary(prim)
{

  // 创建Messenger
  fMessenger = new CompScintSimRunActionMessenger(this);
  fSaveFileName = "CompScintSim"; // 默认文件名

  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);

  // 创建公共ntuple
  analysisManager->CreateNtuple("SourceSpectrum", "Source Spectrum");
  analysisManager->CreateNtupleDColumn("electron"); // id = 0
  analysisManager->CreateNtupleDColumn("proton"); // id = 1
  analysisManager->CreateNtupleDColumn("gamma"); // id = 2
  analysisManager->FinishNtuple();

  // 获取层信息并初始化累加器向量
  ScintillatorLayerManager& layerManager = ScintillatorLayerManager::GetInstance();
  if (!layerManager.IsInitialized())
  {
    layerManager.Initialize(g_ScintillatorGeometry);
  }
  std::vector<G4int> id_lists = layerManager.GetCopynumbers();
  
  // 初始化累加器向量
  // 注意：这里假设copynumbers是连续的，如果不连续，需要调整逻辑
  G4int maxCopyNo = 0;
  for (const auto& id : id_lists) {
    if (id > maxCopyNo) maxCopyNo = id;
  }
  
  // 初始化累加器向量大小为maxCopyNo+1（因为copynumber从0开始）
  fEnergyDeposit.resize(maxCopyNo + 1, G4Accumulable<G4double>(0.));
  fPassingEnergy.resize(maxCopyNo + 1, G4Accumulable<G4double>(0.));
  
  // 为每一层创建Ntuple和直方图
  for (const auto& id : id_lists)
  {
    // 为每一层创建Ntuple和直方图，使用简单的命名，不包含斜杠
    G4String layerPrefix = "Layer_" + std::to_string(id) + "_";
    
    // 创建能量ntuple
    G4String ntupleName = layerPrefix + "Energy";
    G4String ntupleTitle = "Energy deposit and passing in layer " + std::to_string(id);
    analysisManager->CreateNtuple(ntupleName, ntupleTitle);
    analysisManager->CreateNtupleDColumn("energyDeposit"); // 在当前层沉积的能量
    analysisManager->CreateNtupleDColumn("TruelyPassingEnergy"); // 穿过当前层的总能谱(Truely, 不包括多次穿越的重复统计)
    analysisManager->FinishNtuple();

    // 创建光子直方图
    analysisManager->CreateH1(layerPrefix + "Scint", "Scint Wavelength in Crystal", 600, 200.0, 800.0);
    analysisManager->CreateH1(layerPrefix + "Chrnkv", "CherenkovLight Wavelength in Crystal", 600, 200.0, 800.0);
    analysisManager->CreateH1(layerPrefix + "FiberNA", "Wavelength of Light Entering Fiber Numerical Aperture", 600, 200.0, 800.0);
    analysisManager->CreateH1(layerPrefix + "FiberEntry", "Wavelength of Light Entering Fiber", 600, 200.0, 800.0);
  }

  // SourcePosition直方图保持不变
  analysisManager->CreateH2("SourcePosition", "Source Position", 200, -0.5 * g_worldX, 0.5 * g_worldX, 200, -0.5 * g_worldY, 0.5 * g_worldY);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
CompScintSimRunAction::~CompScintSimRunAction() {
  delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// 添加能量沉积累加方法
void CompScintSimRunAction::AddEnergyDeposit(G4int layerID, G4double edep) {
  if (layerID >= 0 && layerID < (G4int)fEnergyDeposit.size()) {
    fEnergyDeposit[layerID] += edep;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// 添加穿透能量累加方法
void CompScintSimRunAction::AddPassingEnergy(G4int layerID, G4double energy) {
  if (layerID >= 0 && layerID < (G4int)fPassingEnergy.size()) {
    fPassingEnergy[layerID] += energy;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4Run *CompScintSimRunAction::GenerateRun()
{
  fRun = new CompScintSimRun();
  return fRun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void CompScintSimRunAction::BeginOfRunAction(const G4Run *)
{
  // 注册所有累加器
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  // 需要单独注册每个累加器
  for (size_t i = 0; i < fEnergyDeposit.size(); i++) {
    accumulableManager->RegisterAccumulable(fEnergyDeposit[i]);
    accumulableManager->RegisterAccumulable(fPassingEnergy[i]);
  }
  
  // 重置所有累加器
  accumulableManager->Reset();
  
  // 设置初始值
  for (size_t i = 0; i < fEnergyDeposit.size(); i++) {
    fEnergyDeposit[i] = 0.;
    fPassingEnergy[i] = 0.;
  }
  
  if (fPrimary)
  {
    G4double energy;
    G4ParticleDefinition *particle;

    fPrimary->isInitialized = false;
    if (fPrimary->GetUseParticleGun())
    {
      particle = fPrimary->GetParticleGun()->GetParticleDefinition();
      energy = fPrimary->GetParticleGun()->GetParticleEnergy();
    }
    else
    {
      particle = fPrimary->GetGPS()->GetParticleDefinition();
      energy = fPrimary->GetGPS()->GetCurrentSource()->GetEneDist()->GetMonoEnergy();
    }

    fRun->SetPrimary(particle, energy);
  }

  // Open an output file
  //
  auto analysisManager = G4AnalysisManager::Instance();
  
  G4String fileName = getNewfileName(fSaveFileName, ".root");
  
  // 在打开文件前设置目录名称
  analysisManager->SetHistoDirectoryName("histograms");
  analysisManager->SetNtupleDirectoryName("ntuples");
  
  if (!analysisManager->OpenFile(fileName))
  {
    G4cerr << "Error: could not open file " << fileName << G4endl;
  }
  else
  {
    G4cout << "Successfully opened file " << fileName << G4endl;
  }
  G4cout << "Using " << analysisManager->GetType() << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void CompScintSimRunAction::EndOfRunAction(const G4Run* run)
{
  G4int runID = run->GetRunID();
  G4cout << "Run " << runID << " ended." << G4endl;

  // 合并所有线程的累加器
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Save histograms & ntuple
  if (isMaster) {
    // 创建包含系统时间的文件名
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream timestamp;
    timestamp << std::put_time(std::localtime(&now_time_t), "%Y%m%d_%H%M%S");
    std::string fileName = "run_" + std::to_string(runID) + "_" + timestamp.str() + ".csv";
    
    static std::mutex fileMutex;
    std::lock_guard<std::mutex> lock(fileMutex); // 使用互斥锁确保线程安全

    std::ofstream outFile(fileName, std::ios::out); // 创建新文件

    // 写入CSV表头
    outFile << "CopyNumber,"
            << "EnergyDeposit(MeV),"
            << "PassingEnergy(MeV),"
            << "ScintPhotonCount,"
            << "CherenkovPhotonCount,"
            << "FiberNAPhotonCount,"
            << "FiberEntryPhotonCount,"
            << "NACollectionRatio,"
            << "FiberEntryRatio\n";

    // 获取所有层的copynumber
    ScintillatorLayerManager& layerManager = ScintillatorLayerManager::GetInstance();
    const std::vector<G4int>& copynumbers = layerManager.GetCopynumbers();
    
    // 遍历每一层，输出详细信息
    for (size_t i = 0; i < copynumbers.size(); i++) {
      G4int copyNo = copynumbers[i];
      
      // 使用累加器获取能量数据
      G4double energyDeposit = fEnergyDeposit[copyNo].GetValue();
      G4double passingEnergy = fPassingEnergy[copyNo].GetValue();
      
      // 获取该层的光子统计信息
      G4String layerPrefix = "Layer_" + std::to_string(copyNo) + "_";
      G4int scintHistoId = analysisManager->GetH1Id(layerPrefix + "Scint");
      G4int cherenkovHistoId = analysisManager->GetH1Id(layerPrefix + "Chrnkv");
      G4int fiberNAHistoId = analysisManager->GetH1Id(layerPrefix + "FiberNA");
      G4int fiberEntryHistoId = analysisManager->GetH1Id(layerPrefix + "FiberEntry");
      
      // 获取计数
      G4int scintillationPhotonCount = analysisManager->GetH1(scintHistoId)->entries();
      G4int cherenkovPhotonCount = analysisManager->GetH1(cherenkovHistoId)->entries();
      G4int fiberNAPhotonCount = analysisManager->GetH1(fiberNAHistoId)->entries();
      G4int fiberEntryPhotonCount = analysisManager->GetH1(fiberEntryHistoId)->entries();
      
      // 计算比例
      G4double totalPhotons = scintillationPhotonCount + cherenkovPhotonCount;
      G4double naRatio = (totalPhotons > 0) ? (G4double)fiberNAPhotonCount / totalPhotons : 0.0;
      G4double entryRatio = (totalPhotons > 0) ? (G4double)fiberEntryPhotonCount / totalPhotons : 0.0;
      
      // 写入该层的数据
      outFile << copyNo << ","
              << energyDeposit / MeV << "," // 转换为MeV
              << passingEnergy / MeV << ","
              << scintillationPhotonCount << ","
              << cherenkovPhotonCount << ","
              << fiberNAPhotonCount << ","
              << fiberEntryPhotonCount << ","
              << naRatio << ","
              << entryRatio << "\n";
    }

    // 关闭文件
    outFile.close();
    
    G4cout << "Simulation results written to CSV file: " << fileName << G4endl;
  }
  
  analysisManager->Write();
  analysisManager->CloseFile();

  G4cout << "Data written to CSV file and analysis file closed." << G4endl;
}

bool CompScintSimRunAction::fileExists(const G4String &fileName)
{
  std::ifstream file(fileName.c_str());
  return file.good();
}

G4String CompScintSimRunAction::getNewfileName(G4String baseFileName, G4String fileExtension)
{
  // 如果 baseFileName 包含扩展名，则先去掉扩展名
  size_t pos = baseFileName.rfind(fileExtension);
  if (pos != std::string::npos && pos == baseFileName.length() - fileExtension.length())
  {
    baseFileName = baseFileName.substr(0, pos);
  }

  G4String fileName;
  int fileIndex = 0;
  
  do
  {
    std::stringstream ss;
    ss << baseFileName;
    if (fileIndex > 0)
    {
      ss << "(" << fileIndex << ")";
    }
    ss << fileExtension;
    fileName = ss.str();
    fileIndex++;
  } while (fileExists(fileName));

  return fileName;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
