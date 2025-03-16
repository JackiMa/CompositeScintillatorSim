#include "ScintillatorLayerManager.hh"
#include "MaterialManager.hh"
#include "config.hh"
#include "utilities.hh"

// ScintillatorLayerInfo方法实现
G4Material* ScintillatorLayerInfo::GetScintMaterial() const {
    return MaterialManager::GetScintillator(scint_material, scint_lightyield, 1, -1);
}
    
G4Material* ScintillatorLayerInfo::GetCoatingMaterial() const {
    return MaterialManager::GetMaterial(coating_material);
}

// ScintillatorLayerManager单例实现
ScintillatorLayerManager& ScintillatorLayerManager::GetInstance() {
    static ScintillatorLayerManager instance;
    return instance;
}

// 构造函数
ScintillatorLayerManager::ScintillatorLayerManager() 
    : m_totalStackHeight(0.0) 
{
}

// 从CSV文件初始化
bool ScintillatorLayerManager::Initialize(const G4String& filename) {
    std::ifstream csvFile(filename);
    if (!csvFile.is_open()) {
        G4ExceptionDescription ed;
        ed << "Cannot open scintillator geometry configuration file: " << filename;
        G4Exception("ScintillatorLayerManager::Initialize",
                  "FileNotFound", FatalException, ed);
        return false;
    }
    
    // 清除现有数据
    m_layerInfoMap.clear();
    m_copynumbers.clear();
    
    // 跳过标题行
    std::string header;
    std::getline(csvFile, header);
    G4cout << "Reading scintillator configuration file, header: " << header << G4endl;
    
    // 读取所有行到内存
    std::string line;
    while (std::getline(csvFile, line)) {
        if (line.empty() || line[0] == '#') {
            continue; // 跳过空行和注释行
        }
        
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> row;
        
        // 解析CSV行
        while (std::getline(ss, item, ',')) {
            row.push_back(item);
        }
        
        // 检查数据完整性
        if (row.size() < 11) {
            G4cout << "WARNING: Skipping malformed line: " << line << G4endl;
            continue;
        }
        
        // 创建层信息对象
        ScintillatorLayerInfo layerInfo;
        layerInfo.copynumber = std::stoi(row[0]);
        layerInfo.readout_face = std::stoi(row[1]);
        layerInfo.scint_material = row[2];
        layerInfo.scint_lightyield = std::stod(row[3]);
        layerInfo.scint_length = std::stod(row[4]);
        layerInfo.scint_width = std::stod(row[5]);
        layerInfo.scint_height = std::stod(row[6]);
        layerInfo.coating_thickness = std::stod(row[7]);
        layerInfo.coating_material = row[8];
        layerInfo.fiber_core_diameter = std::stod(row[9]);
        layerInfo.fiber_cladding_diameter = std::stod(row[10]);
        
        // 存储层信息
        m_layerInfoMap[layerInfo.copynumber] = layerInfo;
        
        // 保存copynumber列表，用于按顺序遍历
        m_copynumbers.push_back(layerInfo.copynumber);
    }
    
    csvFile.close();
    G4cout << "Successfully loaded " << m_layerInfoMap.size() << " scintillator layers." << G4endl;
    
    // 验证copynumber的合法性：必须是从1开始的连续自然数序列
    if (m_copynumbers.empty()) {
        G4ExceptionDescription ed;
        ed << "No valid scintillator layers found in file: " << filename;
        G4Exception("ScintillatorLayerManager::Initialize",
                  "NoLayersFound", FatalException, ed);
        return false;
    }
    
    // 对copynumber进行排序
    std::sort(m_copynumbers.begin(), m_copynumbers.end());
    
    // 检查最小值是否为1
    if (m_copynumbers.front() != 1) {
        G4ExceptionDescription ed;
        ed << "Invalid copynumber sequence: First copynumber must be 1, but found " 
           << m_copynumbers.front() << ". Copynumbers must start from 1.";
        G4Exception("ScintillatorLayerManager::Initialize",
                  "InvalidCopynumberSequence", FatalException, ed);
        return false;
    }
    
    // 检查是否存在重复或跳过的数字
    for (size_t i = 0; i < m_copynumbers.size(); ++i) {
        G4int expected = i + 1; // 期望的copynumber值
        if (m_copynumbers[i] != expected) {
            G4ExceptionDescription ed;
            ed << "Invalid copynumber sequence: Expected " << expected 
               << " at position " << i << ", but found " << m_copynumbers[i] 
               << ". Copynumbers must be consecutive natural numbers starting from 1 without duplicates or gaps.";
            G4Exception("ScintillatorLayerManager::Initialize",
                      "InvalidCopynumberSequence", FatalException, ed);
            return false;
        }
    }
    
    // 计算总高度
    CalculateTotalHeight();
    
    // 输出所有层信息 (调试级别)
    myPrint(DEBUG, "====================== 闪烁体层信息摘要 ======================");
    G4int numLayers = GetCopynumbers().size();
    for (G4int i = 0; i < numLayers; i++) {
        const ScintillatorLayerInfo* layer = GetLayerInfo(i+1);
        if (layer) {
            std::stringstream ss;
            ss << "------------------------------------------------\n";
            ss << "层 copynumber=" << i+1 << " 信息:\n";
            ss << "readout_face: " << layer->readout_face << "\n";
            ss << "scint_material: " << layer->scint_material << "\n";
            ss << "scint_lightyield: " << layer->scint_lightyield << "\n";
            ss << "scint_length: " << layer->GetScintLengthMM()/mm << " mm\n";
            ss << "scint_width: " << layer->GetScintWidthMM()/mm << " mm\n";
            ss << "scint_height: " << layer->GetScintHeightMM()/mm << " mm\n";
            ss << "coating_thickness: " << layer->GetCoatingThicknessNM()/nm << " nm\n";
            ss << "coating_material: " << layer->coating_material << "\n";
            ss << "fiber_core_diameter: " << layer->GetFiberCoreDiameterUM()/um << " um\n";
            ss << "fiber_cladding_diameter: " << layer->GetFiberCladdingDiameterUM()/um << " um\n";
            ss << "------------------------------------------------";
            
            myPrint(DEBUG, ss.str());
        } else {
            myPrint(ERROR, fmt("没有找到copynumber={}的层!", i+1));
        }
    }
    myPrint(DEBUG, "===============================================================");
    
    return true;
}

// 获取特定copynumber的层信息
const ScintillatorLayerInfo* ScintillatorLayerManager::GetLayerInfo(G4int copynumber) const {
    auto it = m_layerInfoMap.find(copynumber);
    if (it != m_layerInfoMap.end()) {
        return &(it->second);
    }
    
    G4cout << "WARNING: Layer with copynumber " << copynumber << " not found!" << G4endl;
    return nullptr;
}

// 获取所有层的copynumber列表
const std::vector<G4int>& ScintillatorLayerManager::GetCopynumbers() const {
    return m_copynumbers;
}

// 获取层的数量
G4int ScintillatorLayerManager::GetNumberOfLayers() const {
    return m_layerInfoMap.size();
}

// 获取所有层的总高度（包含gaps）
G4double ScintillatorLayerManager::GetTotalStackHeight() const {
    return m_totalStackHeight;
}

// 检查是否已初始化
bool ScintillatorLayerManager::IsInitialized() const {
    return !m_layerInfoMap.empty();
}

// 获取所有层的信息
const std::map<G4int, ScintillatorLayerInfo>& ScintillatorLayerManager::GetAllLayerInfo() const {
    return m_layerInfoMap;
}

// 计算总高度
void ScintillatorLayerManager::CalculateTotalHeight() {
    m_totalStackHeight = 0.0;
    
    for (const auto& pair : m_layerInfoMap) {
        const ScintillatorLayerInfo& info = pair.second;
        G4double layer_height = info.scint_height + 2 * (info.coating_thickness * nm / mm);
        m_totalStackHeight += layer_height;
    }
    
    // 添加层间距
    if (m_layerInfoMap.size() > 1) {
        m_totalStackHeight += (m_layerInfoMap.size() - 1) * g_scint_layer_gap / mm;
    }
} 