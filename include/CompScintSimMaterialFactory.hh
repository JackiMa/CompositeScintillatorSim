#ifndef CompScintSimMaterialFactory_hh
#define CompScintSimMaterialFactory_hh 1

#include "G4Material.hh"
#include "G4String.hh"
#include "MyMaterials.hh"

/**
 * @brief 材料工厂类
 * 
 * 提供根据材料名称动态创建材料的功能
 */
class CompScintSimMaterialFactory {
public:
  /**
   * @brief 根据材料名称创建闪烁体材料
   * 
   * @param materialName 材料名称
   * @param lightYield 光产额
   * @param resolutionScale 分辨率尺度
   * @param birksConstant 伯克斯常数
   * @return G4Material* 创建的材料
   */
  static G4Material* CreateScintillatorMaterial(
      const G4String& materialName, 
      G4double lightYield = 1.0, 
      G4double resolutionScale = 1.0, 
      G4double birksConstant = -1.0);
  
  /**
   * @brief 根据材料名称创建包装材料
   * 
   * @param materialName 材料名称
   * @return G4Material* 创建的材料
   */
  static G4Material* CreateCoatingMaterial(const G4String& materialName);
  
  /**
   * @brief 检查材料名称是否被支持
   * 
   * @param materialName 材料名称
   * @return true 材料被支持
   * @return false 材料不被支持
   */
  static bool IsSupportedScintillatorMaterial(const G4String& materialName);
  
  /**
   * @brief 检查包装材料名称是否被支持
   * 
   * @param materialName 材料名称
   * @return true 材料被支持
   * @return false 材料不被支持
   */
  static bool IsSupportedCoatingMaterial(const G4String& materialName);
};

#endif 