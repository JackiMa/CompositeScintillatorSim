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
/// \file CompScintSim/include/CompScintSimRunAction.hh
/// \brief Definition of the CompScintSimRunAction class
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef CompScintSimRunAction_h
#define CompScintSimRunAction_h 1

#include "globals.hh"
#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include <fstream>
#include <vector>

#include "G4AnalysisManager.hh"

#include "CompScintSimRunActionMessenger.hh"

class CompScintSimPrimaryGeneratorAction;
class CompScintSimRun;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;

class CompScintSimRunAction : public G4UserRunAction
{
 public:
  CompScintSimRunAction(CompScintSimPrimaryGeneratorAction* = nullptr);
  ~CompScintSimRunAction();

  G4Run* GenerateRun() override;
  void BeginOfRunAction(const G4Run*) override;
  void EndOfRunAction(const G4Run*) override;

  void SetFileName(const G4String& name) { fSaveFileName = name; } // set file name

  // 添加获取能量值的方法，供EventAction使用
  void AddEnergyDeposit(G4int layerID, G4double edep);
  void AddPassingEnergy(G4int layerID, G4double energy);

 private:
  CompScintSimRun* fRun;
  CompScintSimPrimaryGeneratorAction* fPrimary;

  G4String fSaveFileName;  // 存放输出文件名
  CompScintSimRunActionMessenger* fMessenger; // 运行动作的消息处理器 

  std::ofstream outputFile;

  // 添加用于存储能量数据的累加器向量
  std::vector<G4Accumulable<G4double>> fEnergyDeposit;   // 每层的能量沉积
  std::vector<G4Accumulable<G4double>> fPassingEnergy;   // 每层的穿透能量

  bool fileExists(const G4String& fileName);
  G4String getNewfileName(G4String baseFileName, G4String fileExtension);
};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
