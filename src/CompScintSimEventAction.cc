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
/// \file optical/CompScintSim/src/CompScintSimEventAction.cc
/// \brief Implementation of the CompScintSimEventAction class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "CompScintSimEventAction.hh"
#include "CompScintSimRun.hh"
#include "CompScintSimRunAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4Threading.hh"
#include "G4SystemOfUnits.hh"
#include "config.hh"
#include "utilities.hh"
#include "ScintillatorLayerManager.hh"
#include <fstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
CompScintSimEventAction::CompScintSimEventAction(CompScintSimRunAction* runAction)
    : G4UserEventAction(), fRunAction(runAction)
{
  // 初始化能量沉积数组
  // 获取层信息
  ScintillatorLayerManager& layerManager = ScintillatorLayerManager::GetInstance();
  if (!layerManager.IsInitialized()) {
    layerManager.Initialize(g_ScintillatorGeometry);
  }
  
  // 初始化能量沉积容器大小
  std::vector<G4int> copynumbers = layerManager.GetCopynumbers();
  fLayerCopynumbers = copynumbers;
  
  // 初始化数组大小为层数
  fEnergyDeposit.resize(copynumbers.size(), 0.0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
CompScintSimEventAction::~CompScintSimEventAction() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void CompScintSimEventAction::BeginOfEventAction(const G4Event *)
{
  // 清空处理过的光子ID集合
  processedTrackIDs.clear();
  
  // 清零所有通道的能量沉积
  std::fill(fEnergyDeposit.begin(), fEnergyDeposit.end(), 0.0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void CompScintSimEventAction::EndOfEventAction(const G4Event *event)
{
  // 输出事件进度
  if (1) {
    auto eventID = event->GetEventID();
    auto totalEvents = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
    auto printModulo = totalEvents / 100; // 每1%的事件数
    if ((printModulo > 0) && (eventID % printModulo == 0))
    {
        G4cout << "---> End of event: " << eventID << ", " << (eventID / printModulo) << "% completed" << std::endl;
    }
  }

  // 将数据写入线程CSV文件
  if (fRunAction) {
    // 获取CSV文件名
    G4String csvFileName = fRunAction->GetThreadCsvFileName();
    
    // 追加数据到CSV文件
    std::ofstream outFile(csvFileName, std::ios::app);
    
    if (!outFile.is_open()) {
      G4cerr << "Error: Could not open file " << csvFileName << " for writing!" << G4endl;
      return;
    }
    
    // 写入一行事件数据
    for (size_t i = 0; i < fEnergyDeposit.size(); i++) {
      outFile << fEnergyDeposit[i]/MeV; // 转换为MeV
      if (i < fEnergyDeposit.size() - 1) {
        outFile << ",";
      }
    }
    outFile << "\n";
    outFile.close();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void CompScintSimEventAction::AddEnergyDeposit(G4int copyNumber, G4double edep)
{
  // 找到对应的索引
  for (size_t i = 0; i < fLayerCopynumbers.size(); i++) {
    if (fLayerCopynumbers[i] == copyNumber) {
      fEnergyDeposit[i] += edep;
      return;
    }
  }
  
  // 如果到这里，说明copyNumber不在我们的列表中
  G4cerr << "Warning: Received energy deposit for unknown layer copy number: " << copyNumber << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
