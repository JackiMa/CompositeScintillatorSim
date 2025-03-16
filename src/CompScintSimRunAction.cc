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

  ScintillatorLayerManager& layerManager = ScintillatorLayerManager::GetInstance();
  if (!layerManager.IsInitialized())
  {
    layerManager.Initialize(g_ScintillatorGeometry);
  }
  std::vector<G4int> id_lists = layerManager.GetCopynumbers();
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
G4Run *CompScintSimRunAction::GenerateRun()
{
  fRun = new CompScintSimRun();
  return fRun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void CompScintSimRunAction::BeginOfRunAction(const G4Run *)
{
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
  // G4int nofEvents = run->GetNumberOfEvent();
  // if (nofEvents == 0) return;

  G4int runID = run->GetRunID();
  G4cout << "Run " << runID << " ended." << G4endl;

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
      
      // 这里我们简化处理，不从ntuple中读取数据
      // 假设沉积能量和穿透能量已经在其他地方处理
      G4double energyDeposit = 0.0; // 这里需要根据实际情况获取
      G4double passingEnergy = 0.0; // 这里需要根据实际情况获取
      
      // 获取该层的光子统计信息
      // 根据层号计算相应的直方图索引
      G4int scintHistoId = i * 4;     // 闪烁光直方图ID
      G4int cherenkovHistoId = i * 4 + 1; // 切伦科夫光直方图ID 
      G4int fiberNAHistoId = i * 4 + 2;  // 进入NA的光子直方图ID
      G4int fiberEntryHistoId = i * 4 + 3; // 进入光纤的光子直方图ID
      
      // 获取计数 - 使用entries()方法而不是GetEntries()
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
