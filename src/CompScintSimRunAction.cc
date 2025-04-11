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
#include "G4Threading.hh"

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
  fSaveFileName = "default.csv"; // 默认文件名，带后缀

  // 初始化闪烁体层管理器
  ScintillatorLayerManager& layerManager = ScintillatorLayerManager::GetInstance();
  if (!layerManager.IsInitialized())
  {
    layerManager.Initialize(g_ScintillatorGeometry);
  }
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
void CompScintSimRunAction::BeginOfRunAction(const G4Run* /* run */)
{
  // 创建线程专用的CSV文件名
  G4int threadID = G4Threading::G4GetThreadId();
  std::stringstream csvFilename;
  csvFilename << "thread" << threadID << "_" << fSaveFileName;
  fThreadCsvFileName = csvFilename.str();
  
  // 获取层信息
  ScintillatorLayerManager& layerManager = ScintillatorLayerManager::GetInstance();
  std::vector<G4int> copynumbers = layerManager.GetCopynumbers();
  
  // 为每个线程创建CSV文件并写入表头
  std::ofstream outFile(fThreadCsvFileName, std::ios::out);
  
  // 写入CSV表头（copynumber列表）
  for (size_t i = 0; i < copynumbers.size(); i++) {
    outFile << copynumbers[i];
    if (i < copynumbers.size() - 1) {
      outFile << ",";
    }
  }
  outFile << "\n";
  outFile.close();
  
  G4cout << "Thread " << threadID << " created CSV file: " << fThreadCsvFileName << G4endl;

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
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void CompScintSimRunAction::EndOfRunAction(const G4Run* run)
{
  G4int runID = run->GetRunID();
  G4int threadID = G4Threading::G4GetThreadId();
  
  G4cout << "Run " << runID << " ended on thread " << threadID << G4endl;

  // 主线程负责合并所有线程的CSV文件
  if (isMaster) {
    G4String finalCsvFileName = getNewfileName(fSaveFileName, "");
    
    // 获取层信息，用于写入合并后文件的表头
    ScintillatorLayerManager& layerManager = ScintillatorLayerManager::GetInstance();
    std::vector<G4int> copynumbers = layerManager.GetCopynumbers();
    
    // 创建最终的CSV文件并写入表头
    std::ofstream finalFile(finalCsvFileName, std::ios::out);
    for (size_t i = 0; i < copynumbers.size(); i++) {
      finalFile << copynumbers[i];
      if (i < copynumbers.size() - 1) {
        finalFile << ",";
      }
    }
    finalFile << "\n";
    
    // 合并所有线程的CSV文件，包括主线程(ID=-1)
    // 注意：GetNumberOfRunningWorkerThreads()不包括主线程
    G4int maxThread = G4Threading::GetNumberOfRunningWorkerThreads();
    for (G4int tid = -1; tid < maxThread; tid++) {
      std::stringstream threadCsvFileName;
      threadCsvFileName << "thread" << tid << "_" << fSaveFileName;
      
      std::ifstream threadFile(threadCsvFileName.str());
      if (!threadFile.is_open()) {
        if (tid != -1) { // 如果不是主线程，则输出警告信息
          G4cout << "Warning: Could not open thread file " << threadCsvFileName.str() << G4endl;
        }
        continue;
      }
      
      // 跳过表头
      std::string header;
      std::getline(threadFile, header);
      
      // 复制所有数据行到最终文件
      std::string line;
      while (std::getline(threadFile, line)) {
        finalFile << line << "\n";
      }
      
      threadFile.close();
      
      // 删除线程临时文件
      std::remove(threadCsvFileName.str().c_str());
    }
    
    finalFile.close();
    G4cout << "All thread data merged into final CSV file: " << finalCsvFileName << G4endl;
  }
}

bool CompScintSimRunAction::fileExists(const G4String &fileName)
{
  std::ifstream file(fileName.c_str());
  return file.good();
}

G4String CompScintSimRunAction::getNewfileName(G4String baseFileName, G4String fileExtension)
{
  // 如果baseFileName已经包含了扩展名，则不添加扩展名
  if (fileExtension.empty()) {
    fileExtension = "";
  }

  G4String fileName;
  int fileIndex = 0;
  
  do
  {
    std::stringstream ss;
    ss << baseFileName;
    if (fileIndex > 0)
    {
      size_t extPos = baseFileName.rfind(".");
      if (extPos != std::string::npos) {
        // 在扩展名前插入索引
        ss.str("");
        ss << baseFileName.substr(0, extPos) << "(" << fileIndex << ")" << baseFileName.substr(extPos);
      } else {
        ss << "(" << fileIndex << ")" << fileExtension;
      }
    }
    fileName = ss.str();
    fileIndex++;
  } while (fileExists(fileName));

  return fileName;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
