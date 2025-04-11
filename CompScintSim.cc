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
/// \file CompScintSim/CompScintSim.cc
/// \brief Main program of the CompScintSim example
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// Description: Test of Continuous Process G4Cerenkov
//              and RestDiscrete Process G4Scintillation
//              -- Generation Cerenkov Photons --
//              -- Generation Scintillation Photons --
//              -- Transport of optical Photons --
// Version:     5.0
// Created:     1996-04-30
// Author:      Juliet Armstrong
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include <time.h>

#include "CompScintSimDetectorConstruction.hh"
#ifdef GEANT4_USE_GDML
#include "CompScintSimGDMLDetectorConstruction.hh"
#endif
#include "CompScintSimActionInitialization.hh"
#include "FTFP_BERT.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4OpticalPhysics.hh"
#include "G4RunManagerFactory.hh"
#include "G4Types.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4Scintillation.hh"

#include "config.hh"
#include "utilities.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
namespace
{
  void PrintUsage()
  {
    G4cerr << " Usage: " << G4endl;
#ifdef GEANT4_USE_GDML
    G4cerr << " CompScintSim [-g gdmlfile] [-m macro ] [-u UIsession] [-t "
              "nThreads] [-r seed] [-debug]"
           << G4endl;
#else
    G4cerr << " CompScintSim  [-m macro ] [-u UIsession] [-t nThreads] [-r seed] [-debug]"
           << G4endl;
#endif
    G4cerr << "   note: -t option is available only for multi-threaded mode." << G4endl;
    G4cerr << "   note: -debug enables detailed log output including DEBUG level messages." << G4endl;
  }
} // namespace

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char **argv)
{
  // Evaluate arguments
  //
  if (argc > 10) // 增加最大参数数量以支持-debug
  {
    PrintUsage();
    return 1;
  }
  G4String gdmlfile = "";
  G4String macro;
  G4String session;
#ifdef G4MULTITHREADED
  G4int nThreads = 0;
#endif

  // G4long myseed = 345354; # 固定种子
  G4long myseed = time(0); // 随机种子
  for (G4int i = 1; i < argc; i++)
  {
    if (G4String(argv[i]) == "-debug")
    {
      // -debug是特殊参数，没有对应值
      g_debug_mode = true;
      continue; // 跳过当前参数，继续处理下一个
    }
    
    // 检查是否还有足够的参数（需要成对处理）
    if (i + 1 >= argc)
    {
      PrintUsage();
      return 1;
    }
    
    if (G4String(argv[i]) == "-g")
      gdmlfile = argv[i + 1];
    else if (G4String(argv[i]) == "-m")
      macro = argv[i + 1];
    else if (G4String(argv[i]) == "-u")
      session = argv[i + 1];
    else if (G4String(argv[i]) == "-r")
      myseed = atoi(argv[i + 1]);
#ifdef G4MULTITHREADED
    else if (G4String(argv[i]) == "-t")
    {
      nThreads = G4UIcommand::ConvertToInt(argv[i + 1]);
    }
#endif
    else
    {
      PrintUsage();
      return 1;
    }
    
    // 跳过当前参数对的值部分
    i++;
  }
  
  // 日志级别会根据g_debug_mode自动设置
  
  myPrint(INFO, "Starting CompScintSim application...");
  if (g_debug_mode) {
    myPrint(DEBUG, "调试模式已启用 (g_debug_mode = true)，将显示所有DEBUG级别信息");
  } else {
    myPrint(DEBUG, "当前运行在标准模式，只显示INFO和ERROR级别信息");
    myPrint(DEBUG, "提示: 使用 -debug 命令行参数可启用详细调试输出");
  }

  // Instantiate G4UIExecutive if interactive mode
  G4UIExecutive *ui = nullptr;
  if (macro.size() == 0)
  {
    ui = new G4UIExecutive(argc, argv);
  }

  // Construct the default run manager
  auto runManager = G4RunManagerFactory::CreateRunManager();
#ifdef G4MULTITHREADED
  if (nThreads > 0)
    runManager->SetNumberOfThreads(nThreads);
#endif

  // Seed the random number generator manually
  G4Random::setTheSeed(myseed);

  // Set mandatory initialization classes
  //
  // Detector construction
  if (gdmlfile != "")
  {
#ifdef GEANT4_USE_GDML
    runManager->SetUserInitialization(
        new CompScintSimGDMLDetectorConstruction(gdmlfile));
#else
    G4cout << "Error! Input gdml file specified, but Geant4 wasn't" << G4endl
           << "built with gdml support." << G4endl;
    return 1;
#endif
  }
  else
  {
    runManager->SetUserInitialization(new CompScintSimDetectorConstruction());
  }
  // Physics list
  G4VModularPhysicsList *physicsList = new FTFP_BERT;
  physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());

  if (g_has_opticalPhysics)
  {
    G4OpticalPhysics *opticalPhysics = new G4OpticalPhysics();
    physicsList->RegisterPhysics(opticalPhysics);
  }

  runManager->SetUserInitialization(physicsList);

  runManager->SetUserInitialization(new CompScintSimActionInitialization());

  G4VisManager *visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  G4UImanager *UImanager = G4UImanager::GetUIpointer();

  if (macro.size())
  {
    G4String command = "/control/execute ";
    UImanager->ApplyCommand(command + macro);
  }
  else // Define UI session for interactive mode
  {
    UImanager->ApplyCommand("/control/execute vis.mac");
    if (ui->IsGUI())
      UImanager->ApplyCommand("/control/execute gui.mac");
    ui->SessionStart();

    delete ui;
  }

  delete visManager;
  delete runManager;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
