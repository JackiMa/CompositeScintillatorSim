#ifndef ScintillatorLayerManager_hh
#define ScintillatorLayerManager_hh 1

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

#include "G4ThreeVector.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"
#include "G4Exception.hh"

class MaterialManager;

// 定义一个结构体来存储闪烁体层的所有参数
struct ScintillatorLayerInfo {
    G4int copynumber;                // 探测器编号
    G4int readout_face;              // 读出面方向(0-3)
    G4String scint_material;         // 闪烁体材料名称
    G4double scint_lightyield;       // 闪烁体光产额
    G4double scint_length;           // 闪烁体长度(mm)
    G4double scint_width;            // 闪烁体宽度(mm)
    G4double scint_height;           // 闪烁体高度(mm)
    G4double coating_thickness;      // coating厚度(nm)
    G4String coating_material;       // coating材料名称
    G4double fiber_core_diameter;    // 光纤芯直径(um)
    G4double fiber_cladding_diameter;// 光纤包层直径(um)
    
    // 获取材料实例的便捷方法
    G4Material* GetScintMaterial() const;
    G4Material* GetCoatingMaterial() const;
    
    // 获取转换为正确单位的参数
    G4double GetScintLengthMM() const { return scint_length * mm; }
    G4double GetScintWidthMM() const { return scint_width * mm; }
    G4double GetScintHeightMM() const { return scint_height * mm; }
    G4double GetCoatingThicknessNM() const { return coating_thickness * nm; }
    G4double GetFiberCoreDiameterUM() const { return fiber_core_diameter * um; }
    G4double GetFiberCladdingDiameterUM() const { return fiber_cladding_diameter * um; }
};

// 闪烁体层参数管理类 - 全局单例类，用于管理从CSV文件读取的参数
class ScintillatorLayerManager {
public:
    // 获取单例实例
    static ScintillatorLayerManager& GetInstance();
    
    // 从CSV文件初始化
    bool Initialize(const G4String& filename);
    
    // 获取特定copynumber的层信息
    const ScintillatorLayerInfo* GetLayerInfo(G4int copynumber) const;
    
    // 获取所有层的copynumber列表
    const std::vector<G4int>& GetCopynumbers() const;
    
    // 获取层的数量
    G4int GetNumberOfLayers() const;
    
    // 获取所有层的总高度（包含gaps）
    G4double GetTotalStackHeight() const;
    
    // 检查是否已初始化
    bool IsInitialized() const;
    
    // 获取所有层的信息
    const std::map<G4int, ScintillatorLayerInfo>& GetAllLayerInfo() const;
    
private:
    // 私有构造函数（单例模式）
    ScintillatorLayerManager();
    
    // 禁止复制和赋值
    ScintillatorLayerManager(const ScintillatorLayerManager&) = delete;
    ScintillatorLayerManager& operator=(const ScintillatorLayerManager&) = delete;
    
    // 计算总高度
    void CalculateTotalHeight();
    
    std::map<G4int, ScintillatorLayerInfo> m_layerInfoMap; // 存储每个层的信息，按copynumber索引
    std::vector<G4int> m_copynumbers;                      // 按顺序存储copynumber列表
    G4double m_totalStackHeight;                           // 所有层的总高度（包含gaps）
};

#endif // ScintillatorLayerManager_hh 