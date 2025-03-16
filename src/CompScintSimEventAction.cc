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
#include "CompScintSimStackingAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4Threading.hh"
#include "G4AnalysisManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4Electron.hh"
#include "G4Proton.hh"
#include "G4Gamma.hh"
#include "G4Positron.hh"
#include "CustomScorer.hh"
#include "config.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
CompScintSimEventAction::CompScintSimEventAction(CompScintSimRunAction* runAction)
    : G4UserEventAction(), fRunAction(runAction)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
CompScintSimEventAction::~CompScintSimEventAction() {}


G4THitsMap<G4double>* CompScintSimEventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const
{
  auto hitsCollection
    = static_cast<G4THitsMap<G4double>*>(
        event->GetHCofThisEvent()->GetHC(hcID));

  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("EventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }

  return hitsCollection;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double CompScintSimEventAction::GetSum(G4THitsMap<G4double>* hitsMap) const
{
  G4double sumValue = 0.;
  for ( auto it : *hitsMap->GetMap() ) {
    // hitsMap->GetMap() returns the map of std::map<G4int, G4double*>
    sumValue += *(it.second);
  }
  return sumValue;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void CompScintSimEventAction::BeginOfEventAction(const G4Event *)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void CompScintSimEventAction::EndOfEventAction(const G4Event *event)
{
  auto analysisManager = G4AnalysisManager::Instance();

// 遍历所有 PrimaryVertex
G4PrimaryVertex* primaryVertex = event->GetPrimaryVertex();
while (primaryVertex) {  
    G4PrimaryParticle* primaryParticle = primaryVertex->GetPrimary();
    // 遍历该 vertex 下的所有 primary particle
    while (primaryParticle) {
        // 确保只统计初始生成的粒子

        G4double energy = primaryParticle->GetKineticEnergy();
        G4int particleID = g_id_source_spectrum_gamma;

        const G4ParticleDefinition* particleDef = primaryParticle->GetParticleDefinition();
        if (particleDef) {
            if (particleDef == G4Electron::Definition() || particleDef == G4Positron::Definition()) {
                particleID = g_id_source_spectrum_e;
            } else if (particleDef == G4Proton::Definition()) {
                particleID = g_id_source_spectrum_p;
            } else if (particleDef == G4Gamma::Definition()) {
                particleID = g_id_source_spectrum_gamma;
            }
        }

        // 记录数据
        analysisManager->FillNtupleDColumn(0, particleID, energy);
        analysisManager->AddNtupleRow(0);

        // 继续遍历下一个 primaryParticle
        primaryParticle = primaryParticle->GetNext();
    }

    // 继续遍历下一个 primaryVertex
    primaryVertex = primaryVertex->GetNext();
}





    if (1) {
      auto eventID = event->GetEventID();
      auto totalEvents = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
      auto printModulo = totalEvents / 100; // 每1%的事件数
      if ((printModulo > 0) && (eventID % printModulo == 0))
      {
          G4cout << "---> End of event: " << eventID << ", " << (eventID / printModulo) << "% completed" << std::endl;
      }
    }

ScintillatorLayerManager& layerManager = ScintillatorLayerManager::GetInstance();
std::vector<G4int> id_lists = layerManager.GetCopynumbers();
  for (const auto& id : id_lists){
        // 获取当前层的HitsCollection ID
        int totalEnergyHCID = G4SDManager::GetSDMpointer()->GetCollectionID("scint_layer_" + std::to_string(id) + "/TotalEnergy");
        int truelyPassingEnergyHCID = G4SDManager::GetSDMpointer()->GetCollectionID("scint_layer_" + std::to_string(id) + "/TruelyPassingEnergy");

        // 获取当前层的HitsCollection数据
        auto totalEdep = GetSum(GetHitsCollection(totalEnergyHCID, event));
        auto truelyPassingEng = GetSum(GetHitsCollection(truelyPassingEnergyHCID, event));

        // 获取对应层的Ntuple ID
        // Ntuple名称格式："Layer_X_Energy"
        G4String ntupleName = "Layer_" + std::to_string(id) + "_Energy";
        // 注意：SourceSpectrum是第一个ntuple (ID=0)，然后是各层的Energy ntuple
        G4int ntupleId = id; // 直接使用层ID，因为在RunAction中是按顺序创建的
        
        // 填充该层的能量信息
        analysisManager->FillNtupleDColumn(ntupleId, 0, totalEdep);
        analysisManager->FillNtupleDColumn(ntupleId, 1, truelyPassingEng);
        analysisManager->AddNtupleRow(ntupleId);
        
        // 使用RunAction的累加器累积当前事件的能量数据
        if (fRunAction) {
            fRunAction->AddEnergyDeposit(id, totalEdep);
            fRunAction->AddPassingEnergy(id, truelyPassingEng);
        }
    }

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
