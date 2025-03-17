#ifndef MaterialManager_hh
#define MaterialManager_hh 1

#include "G4Material.hh"
#include "G4String.hh"
#include "MyMaterials.hh"
#include <map>
#include <functional>
#include <vector>

/**
 * @brief 材料管理器类，提供通过字符串获取材料的功能
 * 
 * 这个类是MyMaterials的扩展，允许通过字符串动态获取材料
 */
class MaterialManager {
private:
    // 私有静态方法，用于初始化材料映射
    static void InitializeMaterialMaps();
    
    // 材料名称到材料创建函数的映射
    static std::map<G4String, std::function<G4Material*()>> materialMap;
    static std::map<G4String, std::function<G4Material*(G4double, G4double, G4double)>> scintillatorMap;
    
    // 标记是否已初始化
    static bool mapsInitialized;

public:
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
     * @param attenuationLength 吸收长度
     * @param birksConstant 伯克斯常数
     * @return G4Material* 材料指针，如果不存在则返回nullptr
     */
    static G4Material* GetScintillator(
        const G4String& materialName, 
        G4double lightYield = 1.0, 
        G4double attenuationLength = 1.0, 
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
};

#endif 