#include "MaterialManager.hh"

// 初始化静态成员变量
std::map<G4String, std::function<G4Material*()>> MaterialManager::materialMap;
std::map<G4String, std::function<G4Material*(G4double, G4double, G4double)>> MaterialManager::scintillatorMap;
bool MaterialManager::mapsInitialized = false;

// 初始化材料映射方法
void MaterialManager::InitializeMaterialMaps() {
    if (mapsInitialized) return;
    
    // 普通材料映射
    materialMap["Boron"] = []() { return MyMaterials::Boron(); };
    materialMap["TantalumFoil"] = []() { return MyMaterials::TantalumFoil(); };
    materialMap["Graphite"] = []() { return MyMaterials::Graphite(); };
    materialMap["PEEK"] = []() { return MyMaterials::PEEK(); };
    materialMap["Vacuum"] = []() { return MyMaterials::Vacuum(); };
    materialMap["Air"] = []() { return MyMaterials::Air(); };
    materialMap["AirKiller"] = []() { return MyMaterials::AirKiller(); };
    materialMap["Water"] = []() { return MyMaterials::Water(); };
    materialMap["Silicon"] = []() { return MyMaterials::Silicon(); };
    materialMap["Aluminium"] = []() { return MyMaterials::Aluminium(); };
    materialMap["Al"] = []() { return MyMaterials::Aluminium(); };
    materialMap["Iron"] = []() { return MyMaterials::Iron(); };
    materialMap["Lead"] = []() { return MyMaterials::Lead(); };
    materialMap["Brass"] = []() { return MyMaterials::Brass(); };
    materialMap["Tungsten"] = []() { return MyMaterials::Tungsten(); };
    materialMap["TungstenLight"] = []() { return MyMaterials::TungstenLight(); };
    materialMap["Quartz"] = []() { return MyMaterials::Quartz(); };
    materialMap["OpticalGrease"] = []() { return MyMaterials::OpticalGrease(); };
    materialMap["PVC"] = []() { return MyMaterials::PVC(); };
    materialMap["CuAir"] = []() { return MyMaterials::CuAir(); };
    materialMap["Cu"] = []() { return MyMaterials::Cu(); };
    materialMap["LAPPD_Average"] = []() { return MyMaterials::LAPPD_Average(); };
    materialMap["StainlessSteel"] = []() { return MyMaterials::StainlessSteel(); };
    materialMap["Copper"] = []() { return MyMaterials::Copper(); };
    materialMap["ESR_Vikuiti"] = []() { return MyMaterials::ESR_Vikuiti(); };
    materialMap["LAPPD_Window"] = []() { return MyMaterials::LAPPD_Window(); };
    materialMap["LAPPD_MCP"] = []() { return MyMaterials::LAPPD_MCP(); };
    materialMap["Epoxy"] = []() { return MyMaterials::Epoxy(); };
    materialMap["LAPPD_PCB"] = []() { return MyMaterials::LAPPD_PCB(); };
    materialMap["GarthTypographicAlloy"] = []() { return MyMaterials::GarthTypographicAlloy(); };
    materialMap["Tyvek"] = []() { return MyMaterials::Tyvek(); };
    materialMap["PMMA"] = []() { return MyMaterials::PMMA(); };
    materialMap["Shashlik_Polystyrene"] = []() { return MyMaterials::Shashlik_Polystyrene(); };
    
    // 闪烁体材料映射
    scintillatorMap["BaF2"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::BaF2(ly, rs, bc); };
    scintillatorMap["NaI_Tl"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::NaI_Tl(ly, rs, bc); };
    scintillatorMap["CsI_Tl"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::CsI_Tl(ly, rs, bc); };
    scintillatorMap["CsI"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::CsI(ly, rs, bc); };
    scintillatorMap["GOS"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::GOS(ly, rs, bc); };
    scintillatorMap["LSO"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::LSO(ly, rs, bc); };
    scintillatorMap["YSO"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::YSO(ly, rs, bc); };
    scintillatorMap["LYSO"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::LYSO(ly, rs, bc); };
    scintillatorMap["LuAG_Ce"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::LuAG_Ce(ly, rs, bc); };
    scintillatorMap["LuAG_Pr"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::LuAG_Pr(ly, rs, bc); };
    scintillatorMap["DSB_Ce"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::DSB_Ce(ly, rs, bc); };
    scintillatorMap["SiO2_Ce"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::SiO2_Ce(ly, rs, bc); };
    scintillatorMap["BGO"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::BGO(ly, rs, bc); };
    scintillatorMap["PWO"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::PWO(ly, rs, bc); };
    scintillatorMap["CWO"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::CWO(ly, rs, bc); };
    scintillatorMap["YAG_Ce"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::YAG_Ce(ly, rs, bc); };
    scintillatorMap["GAGG_Ce_Mg"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::GAGG_Ce_Mg(ly, rs, bc); };
    scintillatorMap["GAGG_ILM"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::GAGG_ILM(ly, rs, bc); };
    scintillatorMap["GFAG"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::GFAG(ly, rs, bc); };
    scintillatorMap["GYAGG"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::GYAGG(ly, rs, bc); };
    scintillatorMap["GAGG_very_fast"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::GAGG_very_fast(ly, rs, bc); };
    scintillatorMap["GAGG_slow"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::GAGG_slow(ly, rs, bc); };
    scintillatorMap["Polystyrene"] = [](G4double ly, G4double rs, G4double bc) { return MyMaterials::Polystyrene(ly, rs, bc); };
    
    // 标记为已初始化
    mapsInitialized = true;
}

// 通过材料名称获取材料
G4Material* MaterialManager::GetMaterial(const G4String& materialName) {
    // 确保映射已初始化
    if (!mapsInitialized) {
        InitializeMaterialMaps();
    }
    
    // 查找普通材料
    auto it = materialMap.find(materialName);
    if (it != materialMap.end()) {
        return it->second();
    }
    
    // 如果不是普通材料，返回nullptr
    return nullptr;
}

// 通过材料名称获取闪烁体材料
G4Material* MaterialManager::GetScintillator(
    const G4String& materialName, 
    G4double lightYield, 
    G4double resolutionScale, 
    G4double birksConstant) {
    // 确保映射已初始化
    if (!mapsInitialized) {
        InitializeMaterialMaps();
    }
    
    // 查找闪烁体材料
    auto it = scintillatorMap.find(materialName);
    if (it != scintillatorMap.end()) {
        return it->second(lightYield, resolutionScale, birksConstant);
    }
    
    // 如果不是闪烁体材料，返回nullptr
    return nullptr;
}

// 检查是否支持指定的材料
bool MaterialManager::IsSupportedMaterial(const G4String& materialName) {
    // 确保映射已初始化
    if (!mapsInitialized) {
        InitializeMaterialMaps();
    }
    
    return materialMap.find(materialName) != materialMap.end();
}

// 检查是否支持指定的闪烁体材料
bool MaterialManager::IsSupportedScintillator(const G4String& materialName) {
    // 确保映射已初始化
    if (!mapsInitialized) {
        InitializeMaterialMaps();
    }
    
    return scintillatorMap.find(materialName) != scintillatorMap.end();
}

// 获取所有支持的材料名称列表
std::vector<G4String> MaterialManager::GetSupportedMaterials() {
    // 确保映射已初始化
    if (!mapsInitialized) {
        InitializeMaterialMaps();
    }
    
    std::vector<G4String> materials;
    materials.reserve(materialMap.size());
    
    for (const auto& pair : materialMap) {
        materials.push_back(pair.first);
    }
    
    return materials;
}

// 获取所有支持的闪烁体材料名称列表
std::vector<G4String> MaterialManager::GetSupportedScintillators() {
    // 确保映射已初始化
    if (!mapsInitialized) {
        InitializeMaterialMaps();
    }
    
    std::vector<G4String> scintillators;
    scintillators.reserve(scintillatorMap.size());
    
    for (const auto& pair : scintillatorMap) {
        scintillators.push_back(pair.first);
    }
    
    return scintillators;
} 