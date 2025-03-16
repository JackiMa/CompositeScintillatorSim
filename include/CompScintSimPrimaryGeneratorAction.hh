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
/// \file CompScintSim/include/CompScintSimPrimaryGeneratorAction.hh
/// \brief Definition of the CompScintSimPrimaryGeneratorAction class
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef CompScintSimPrimaryGeneratorAction_h
#define CompScintSimPrimaryGeneratorAction_h 1

#include "globals.hh"
#include "G4ParticleGun.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "CompScintSimDetectorConstruction.hh"
#include <random>
#include "G4GeneralParticleSource.hh"
#include "G4ThreeVector.hh"
#include <vector>
#include <string>

class G4Event;
class CompScintSimPrimaryGeneratorMessenger;

// 定义粒子源结构体
struct MyGPSSource {
    G4int id;              // 源的唯一标识符
    G4String particleType;  // 粒子类型
    G4double energy;        // 粒子能量 (单位：MeV)
    G4int count;            // 粒子数量

    MyGPSSource(G4int sourceId, const G4String& type, G4double e, G4int c)
        : id(sourceId), particleType(type), energy(e), count(c) {}
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class CompScintSimPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
 public:
  CompScintSimPrimaryGeneratorAction(CompScintSimDetectorConstruction* detectorConstruction);
  ~CompScintSimPrimaryGeneratorAction();

  void GeneratePrimaries(G4Event*) override;

  void InitializeProjectionArea();
  bool isInitialized = false;

  G4ParticleGun* GetParticleGun() { return fParticleGun; }
  G4GeneralParticleSource* GetGPS() { return fGPS; }

  void UseParticleGun(G4bool useGun) { useParticleGun = useGun; }
  void SetUseParticleGun(G4bool useGun);
  G4bool GetUseParticleGun() { return useParticleGun; }

  // 添加GPS源管理方法
  void AddGPSSource(const G4String& particleType, G4double energy, G4int count);
  void ClearGPSSources();
  void ListGPSSources() const;
  
 private:
  G4ParticleGun* fParticleGun;
  G4GeneralParticleSource* fGPS; // 使用 GPS
  bool useParticleGun; // 标记使用哪种粒子源

  CompScintSimPrimaryGeneratorMessenger* fGunMessenger;
  const CompScintSimDetectorConstruction* detector;

  CompScintSimDetectorConstruction* fDetectorConstruction;
  
  G4double minX, maxX, minY, maxY, z_pos;
  std::uniform_real_distribution<> disX;
  std::uniform_real_distribution<> disY;
  std::mt19937 gen;

  // 存储GPS源信息的向量
  std::vector<MyGPSSource> fGPSSources;

  // 跟踪当前事件索引和总粒子数
  G4int fCurrentEventIndex;
  G4int fTotalParticleCount;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*CompScintSimPrimaryGeneratorAction_h*/
