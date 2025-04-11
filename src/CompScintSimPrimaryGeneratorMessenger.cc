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
/// \file CompScintSim/src/CompScintSimPrimaryGeneratorMessenger.cc
/// \brief Implementation of the CompScintSimPrimaryGeneratorMessenger class
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "CompScintSimPrimaryGeneratorMessenger.hh"
#include "CompScintSimPrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "utilities.hh"
#include <sstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CompScintSimPrimaryGeneratorMessenger::CompScintSimPrimaryGeneratorMessenger(
  CompScintSimPrimaryGeneratorAction* CompScintSimGun)
  : G4UImessenger()
  , fCompScintSimAction(CompScintSimGun)
{
  fGunDir = new G4UIdirectory("/CompScintSim/gun/");
  fGunDir->SetGuidance("PrimaryGenerator control");

  fPolarCmd =
    new G4UIcmdWithADoubleAndUnit("/CompScintSim/gun/optPhotonPolar", this);
  fPolarCmd->SetGuidance("Set linear polarization");
  fPolarCmd->SetGuidance("  angle w.r.t. (k,n) plane");
  fPolarCmd->SetParameterName("angle", true);
  fPolarCmd->SetUnitCategory("Angle");
  fPolarCmd->SetDefaultValue(-360.0);
  fPolarCmd->SetDefaultUnit("deg");
  fPolarCmd->AvailableForStates(G4State_Idle);

  fSetUseParticleGunCmd = new G4UIcmdWithABool("/CompScintSim/generator/useParticleGun", this);
  fSetUseParticleGunCmd->SetGuidance("Set whether to use ParticleGun or GPS.");
  fSetUseParticleGunCmd->SetParameterName("useParticleGun", true);
  fSetUseParticleGunCmd->SetDefaultValue(true);
  
  // 创建GPS源相关命令
  // 添加GPS源命令
  fAddGPSSourceCmd = new G4UIcommand("/gps/my_source/add", this);
  fAddGPSSourceCmd->SetGuidance("Add a GPS source with specified particle type, energy, and count");
  fAddGPSSourceCmd->SetGuidance("  Usage: /gps/my_source/add [particle] [energy] [unit] [count]");
  
  G4UIparameter* paramParticle = new G4UIparameter("particle", 's', false);
  paramParticle->SetGuidance("Particle type (e.g., 'e-', 'gamma', 'proton')");
  fAddGPSSourceCmd->SetParameter(paramParticle);
  
  G4UIparameter* paramEnergy = new G4UIparameter("energy", 'd', false);
  paramEnergy->SetGuidance("Particle energy value");
  fAddGPSSourceCmd->SetParameter(paramEnergy);
  
  G4UIparameter* paramUnit = new G4UIparameter("unit", 's', false);
  paramUnit->SetGuidance("Energy unit (eV, keV, MeV, GeV)");
  paramUnit->SetParameterCandidates("eV keV MeV GeV");
  fAddGPSSourceCmd->SetParameter(paramUnit);
  
  G4UIparameter* paramCount = new G4UIparameter("count", 'i', false);
  paramCount->SetGuidance("Number of particles to generate");
  fAddGPSSourceCmd->SetParameter(paramCount);
  
  // 列出GPS源命令
  fListGPSSourcesCmd = new G4UIcommand("/gps/my_source/list", this);
  fListGPSSourcesCmd->SetGuidance("List all defined GPS sources");
  fListGPSSourcesCmd->AvailableForStates(G4State_PreInit, G4State_Idle, G4State_GeomClosed, G4State_EventProc);
  
  // 清空GPS源命令
  fClearGPSSourcesCmd = new G4UIcommand("/gps/my_source/clear", this);
  fClearGPSSourcesCmd->SetGuidance("Clear all defined GPS sources");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CompScintSimPrimaryGeneratorMessenger::~CompScintSimPrimaryGeneratorMessenger()
{
  delete fPolarCmd;
  delete fGunDir;
  delete fSetUseParticleGunCmd;
  
  // 删除GPS源相关命令
  delete fAddGPSSourceCmd;
  delete fListGPSSourcesCmd;
  delete fClearGPSSourcesCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CompScintSimPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if (command == fSetUseParticleGunCmd) {
    G4bool useGun = fSetUseParticleGunCmd->GetNewBoolValue(newValue);
    myPrint(DEBUG, fmt("Setting particle generator: useParticleGun = {}", useGun ? "true" : "false"));
    fCompScintSimAction->SetUseParticleGun(useGun);
  }
  else if (command == fAddGPSSourceCmd) {
    // 解析命令参数
    std::istringstream is(newValue);
    G4String particleType;
    G4double energy;
    G4String unit;
    G4int count;
    
    is >> particleType >> energy >> unit >> count;
    
    // 单位转换
    G4double energyValue = energy;
    if (unit == "eV") energyValue *= eV;
    else if (unit == "keV") energyValue *= keV;
    else if (unit == "MeV") energyValue *= MeV;
    else if (unit == "GeV") energyValue *= GeV;
    
    myPrint(DEBUG, fmt("Adding particle source: {} {} {} {}", particleType, energy, unit, count));
    fCompScintSimAction->AddGPSSource(particleType, energyValue, count);
    myPrint(INFO, fmt("Added particle source: {} {} {} ({} particles)", particleType, energy, unit, count));
  }
  else if (command == fClearGPSSourcesCmd) {
    myPrint(DEBUG, "Clearing all particle sources");
    fCompScintSimAction->ClearGPSSources();
    myPrint(INFO, "All particle sources cleared");
  }
  else if (command == fListGPSSourcesCmd) {
    myPrint(DEBUG, "Listing all particle sources");
    myPrint(INFO, "Command /gps/my_source/list received");
    fCompScintSimAction->ListGPSSources();
  }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
