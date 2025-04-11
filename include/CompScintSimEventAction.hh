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
/// \file optical/CompScintSim/include/CompScintSimEventAction.hh
/// \brief Definition of the CompScintSimEventAction class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef CompScintSimEventAction_h
#define CompScintSimEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include <set>
#include <vector>

class CompScintSimRunAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class CompScintSimEventAction : public G4UserEventAction
{
 public:
  CompScintSimEventAction(CompScintSimRunAction* runAction);
  ~CompScintSimEventAction() override;

  void BeginOfEventAction(const G4Event* event) override;
  void EndOfEventAction(const G4Event* event) override;
  
  // 添加能量沉积方法，供SteppingAction使用
  void AddEnergyDeposit(G4int copyNumber, G4double edep);
  
  // 用于考虑光子是否穿过数值孔径，记录trackID，避免重复统计
  std::set<G4int> processedTrackIDs;

 private:
  CompScintSimRunAction* fRunAction = nullptr;
  
  // 存储各层能量沉积
  std::vector<G4double> fEnergyDeposit;
  
  // 存储层copynumber
  std::vector<G4int> fLayerCopynumbers;
};
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
