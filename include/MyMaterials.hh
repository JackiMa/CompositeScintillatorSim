// Lab 27 CERN

#ifndef MyMaterials_hh
#define MyMaterials_hh

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4OpticalSurface.hh"
#include <map>
#include <functional>
#include <vector>

// !! Please check if the light yield is correct before using.

/**
 * @brief 材料工厂类，提供创建和管理各种材料的能力
 * 
 * 该类提供两种方式获取材料：
 * 1. 通过静态方法直接访问特定材料（如MyMaterials::Air()）
 * 2. 通过字符串动态获取材料（如MyMaterials::GetMaterial("Air")）
 */
class MyMaterials
{
private:
  // 私有静态方法，用于初始化材料映射
  static void InitializeMaterialMaps();
  
  // 材料名称到材料创建函数的映射
  static std::map<G4String, std::function<G4Material*()>> materialMap;
  static std::map<G4String, std::function<G4Material*(G4double, G4double, G4double)>> scintillatorMap;
  
  // 标记是否已初始化
  static bool mapsInitialized;

public:
  MyMaterials();
  ~MyMaterials();
  
  /**
   * @brief 通过材料名称获取材料
   * 
   * @param materialName 材料名称
   * @return G4Material* 材料指针，如果不存在则返回nullptr
   */
  static G4Material* GetMaterial(const G4String& materialName);
  
  /**
   * @brief 通过材料名称获取闪烁体材料
   * 
   * @param materialName 材料名称
   * @param lightYield 光产额
   * @param resolutionScale 分辨率尺度
   * @param birksConstant 伯克斯常数
   * @return G4Material* 材料指针，如果不存在则返回nullptr
   */
  static G4Material* GetScintillator(
      const G4String& materialName, 
      G4double lightYield = 1.0, 
      G4double resolutionScale = 1.0, 
      G4double birksConstant = -1.0);
  
  /**
   * @brief 检查是否支持指定的材料
   * 
   * @param materialName 材料名称
   * @return true 支持该材料
   * @return false 不支持该材料
   */
  static bool IsSupportedMaterial(const G4String& materialName);
  
  /**
   * @brief 检查是否支持指定的闪烁体材料
   * 
   * @param materialName 材料名称
   * @return true 支持该材料
   * @return false 不支持该材料
   */
  static bool IsSupportedScintillator(const G4String& materialName);
  
  /**
   * @brief 获取所有支持的材料名称列表
   * 
   * @return std::vector<G4String> 材料名称列表
   */
  static std::vector<G4String> GetSupportedMaterials();
  
  /**
   * @brief 获取所有支持的闪烁体材料名称列表
   * 
   * @return std::vector<G4String> 闪烁体材料名称列表
   */
  static std::vector<G4String> GetSupportedScintillators();

  // new 
  static G4Material* Boron();
  static G4Material* TantalumFoil();
  static G4Material* Graphite();
  static G4Material* PEEK();

  // old 
  static G4Material* Vacuum();
  static G4Material* Air();
  static G4Material* AirKiller(); // special material with same prop of air but absorbing light
  static G4Material* Water();
  static G4Material* Silicon();
  static G4Material* Aluminium();
  static G4Material* Iron();
  static G4Material* Lead();
  static G4Material* Brass();
  static G4Material* Tungsten();
  static G4Material* TungstenLight();
  static G4Material* CopperTungstenAlloy(const G4double& WFrac);
  static G4Material* Quartz();
  static G4Material* OpticalGrease();


  static G4Material* BaF2(double user_lightyield,double scaleFactor,double user_birks); // !! 光学性质照抄LYSO
  static G4Material* NaI_Tl(double user_lightyield,double scaleFactor,double user_birks); // !! 光学性质照抄LYSO
  static G4Material* CsI_Tl(double user_lightyield,double scaleFactor,double user_birks); // !! 光学性质照抄LYSO
  static G4Material* CsI(double user_lightyield,double scaleFactor,double user_birks); // !! 光学性质照抄LYSO
  static G4Material* GOS(double user_lightyield,double scaleFactor,double user_birks); // !! 光学性质照抄BGO
  static G4Material* LSO(double user_lightyield,double scaleFactor,double user_birks); // !! 光学性质照抄LYSO
  static G4Material* YSO(double user_lighyield,double scaleFactor,double user_birks);
  static G4Material* LYSO(double user_lightyield,double scaleFactor,double user_birks);
  static G4Material* LuAG_Ce(double user_lightyield,double scaleFactor,double user_birks); //
  static G4Material* LuAG_Pr(double user_lightyield,double scaleFactor,double user_birks);
  static G4Material* DSB_Ce(double user_lightyield,double scaleFactor,double user_birks);
  static G4Material* SiO2_Ce(double user_lightyield,double scaleFactor,double user_birks);
  static G4Material* BGO            (double user_lightyield,double scaleFactor,double user_birks);
  static G4Material* PWO            (double user_lightyield,double scaleFactor,double user_birks);
  static G4Material* CWO            (double user_lightyield,double scaleFactor,double user_birks); // !! 光学性质照抄PWO
  static G4Material* YAG_Ce         (double user_lightyield,double scaleFactor,double user_birks);
  static G4Material* GAGG_Ce_Mg     (double user_lightyield,double scaleFactor,double user_birks);
  static G4Material* GAGG_ILM       (double user_lightyield,double scaleFactor,double user_birks);
  static G4Material* GFAG           (double user_lightyield,double scaleFactor,double user_birks);
  static G4Material* GYAGG          (double user_lightyield,double scaleFactor,double user_birks);
  static G4Material* GAGG_very_fast (double user_lightyield,double scaleFactor,double user_birks);
  static G4Material* GAGG_slow      (double user_lightyield,double scaleFactor,double user_birks);
  static G4Material* Polystyrene    (double user_lightyield,double scaleFactor,double user_birks);
  static G4Material* PLEX           (double scaleFactor);
  static G4Material* FlurPoly       (double scaleFactor);
  static G4Material* PVC();
  static G4Material* CuAir(); //crystal tube
  static G4Material* Cu(); // Wires
  static G4Material* LAPPD_Average(); // average LAPPD material to fill space between front and back sections
  static G4Material* StainlessSteel(); 
  static G4Material* Copper(); 
  static G4Material* ESR_Vikuiti(); 
  static G4Material* LAPPD_Window(); // LAPPD quartz window
  static G4Material* LAPPD_MCP(); // material of MCP inside LAPPD
  static G4Material* Epoxy(); // Epoxy resin usually used in PCB materials. For the PCB of the LAPPD backplane
  static G4Material* LAPPD_PCB(); // material of PCB on the backplance of LAPPD
  static G4Material* GarthTypographicAlloy(); // Pb 84% - Sb 12% - 4% Sn - density 10 g/cm3
  static G4Material* Tyvek();
  static G4Material* Pethylene(double scaleFactor);
  static G4Material* PMMA();
  static G4Material* PMMA_Y11(double scaleFactor);
  static G4Material* PMMA_YS2(double scaleFactor);
  static G4Material* PMMA_YS4(double scaleFactor);
  static G4Material* Shashlik_Polystyrene();


  static G4MaterialPropertiesTable* ESR(double esrTransmittance);      // ESR reflector surface
  static G4MaterialPropertiesTable* Teflon();      // Teflon reflector surface
  static G4MaterialPropertiesTable* TiO2();      // TiO2 reflector surface
  static G4MaterialPropertiesTable* ABS_SURF(G4double Reflectivity, G4double specularLobe, G4double specularSpike, G4double backScatter ); // Absorber internal surface
  static G4MaterialPropertiesTable* crystal_depo_SURF(); // crystal lateral surface
  static G4MaterialPropertiesTable* clear_fiber_optical();

  static G4OpticalSurface* surf_Teflon();
  static G4OpticalSurface* surf_TiO2();
  static G4OpticalSurface* surf_GapToClearCrystal();
  static G4OpticalSurface* surf_GlassToPhotocathode();
  

  static G4double fromNmToEv(G4double wavelength);
  static G4double fromEvToNm(G4double energy);
  static G4double CalculateSellmeier(int size, G4double indexZero, G4double *nVec, G4double *lVec, G4double wavelength);
};

#endif
