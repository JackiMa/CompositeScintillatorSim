#ifndef CONFIG_HH
#define CONFIG_HH


#include <string>

#include "G4ThreeVector.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"

#include "MyMaterials.hh"
#include "ScintillatorLayerManager.hh"


// g_ means global_

// 光学表面
inline G4OpticalSurface *g_surf_Teflon = MyMaterials::surf_Teflon();

// switch
inline G4bool g_has_opticalPhysics = false;  // 是否模拟光学过程
inline G4bool g_has_cherenkov = true;       // 是否考虑切伦科夫光

// world
inline G4double g_worldX = 20 * cm;
inline G4double g_worldY = 20 * cm;
inline G4double g_worldZ = 20 * cm;
inline G4Material *g_world_material = MyMaterials::Vacuum();

// scintillator
inline G4String g_ScintillatorGeometry = "../Data/ScintillatorGeometry.csv";
inline G4double g_scint_layer_gap = 1 * mm;
inline G4double g_hole_diameter_ratio = 1; // 闪烁体开孔与光纤外径的比值

// light guide
inline G4double g_lg_na = 0.22;     // 光导数值孔径。-1表示根据前面定义的材料和实际光子能量进行计算
inline G4double g_lg_length = 3 * cm; // 光导长度

// source
inline G4double g_source_scale = 1; // 源的尺度是scintillator投影的若干倍


// data process
inline G4int g_id_source_spectrum_e = 0;
inline G4int g_id_source_spectrum_p = 1;
inline G4int g_id_source_spectrum_gamma = 2;

// 定义全局变量g_debug_mode，默认为false
inline G4bool g_debug_mode = false;

#endif // CONFIG_HH