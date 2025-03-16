#include "CompScintSimMaterialFactory.hh"
#include "G4Exception.hh"
#include "G4ExceptionSeverity.hh"
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <functional>

// 定义函数指针类型 - 闪烁体材料创建函数
using ScintillatorMaterialCreator = std::function<G4Material*(G4double, G4double, G4double)>;

// 闪烁体材料创建函数映射 - 使用std::map替代std::unordered_map以避免哈希问题
static const std::map<G4String, ScintillatorMaterialCreator> scintillatorCreators = {
    {"YAG_Ce",     [](G4double ly, G4double rs, G4double bc) { return MyMaterials::YAG_Ce(ly, rs, bc); }},
    {"LYSO",       [](G4double ly, G4double rs, G4double bc) { return MyMaterials::LYSO(ly, rs, bc); }},
    {"BGO",        [](G4double ly, G4double rs, G4double bc) { return MyMaterials::BGO(ly, rs, bc); }},
    {"GAGG_Ce_Mg", [](G4double ly, G4double rs, G4double bc) { return MyMaterials::GAGG_Ce_Mg(ly, rs, bc); }},
    {"LuAG_Ce",    [](G4double ly, G4double rs, G4double bc) { return MyMaterials::LuAG_Ce(ly, rs, bc); }},
    {"CsI_Tl",     [](G4double ly, G4double rs, G4double bc) { return MyMaterials::CsI_Tl(ly, rs, bc); }},
    {"NaI_Tl",     [](G4double ly, G4double rs, G4double bc) { return MyMaterials::NaI_Tl(ly, rs, bc); }},
    {"CsI",        [](G4double ly, G4double rs, G4double bc) { return MyMaterials::CsI(ly, rs, bc); }},
    {"BaF2",       [](G4double ly, G4double rs, G4double bc) { return MyMaterials::BaF2(ly, rs, bc); }},
    {"GOS",        [](G4double ly, G4double rs, G4double bc) { return MyMaterials::GOS(ly, rs, bc); }},
    {"LSO",        [](G4double ly, G4double rs, G4double bc) { return MyMaterials::LSO(ly, rs, bc); }},
    {"YSO",        [](G4double ly, G4double rs, G4double bc) { return MyMaterials::YSO(ly, rs, bc); }},
    {"LuAG_Pr",    [](G4double ly, G4double rs, G4double bc) { return MyMaterials::LuAG_Pr(ly, rs, bc); }},
    {"DSB_Ce",     [](G4double ly, G4double rs, G4double bc) { return MyMaterials::DSB_Ce(ly, rs, bc); }},
    {"SiO2_Ce",    [](G4double ly, G4double rs, G4double bc) { return MyMaterials::SiO2_Ce(ly, rs, bc); }},
    {"PWO",        [](G4double ly, G4double rs, G4double bc) { return MyMaterials::PWO(ly, rs, bc); }},
    {"CWO",        [](G4double ly, G4double rs, G4double bc) { return MyMaterials::CWO(ly, rs, bc); }},
    {"GAGG_ILM",   [](G4double ly, G4double rs, G4double bc) { return MyMaterials::GAGG_ILM(ly, rs, bc); }},
    {"GFAG",       [](G4double ly, G4double rs, G4double bc) { return MyMaterials::GFAG(ly, rs, bc); }},
    {"GYAGG",      [](G4double ly, G4double rs, G4double bc) { return MyMaterials::GYAGG(ly, rs, bc); }},
    {"GAGG_very_fast", [](G4double ly, G4double rs, G4double bc) { return MyMaterials::GAGG_very_fast(ly, rs, bc); }},
    {"GAGG_slow",  [](G4double ly, G4double rs, G4double bc) { return MyMaterials::GAGG_slow(ly, rs, bc); }},
    {"Polystyrene",[](G4double ly, G4double rs, G4double bc) { return MyMaterials::Polystyrene(ly, rs, bc); }}
};

// 定义函数指针类型 - 包装材料创建函数
using CoatingMaterialCreator = std::function<G4Material*()>;

// 包装材料创建函数映射 - 使用std::map替代std::unordered_map以避免哈希问题
static const std::map<G4String, CoatingMaterialCreator> coatingCreators = {
    {"Al",    []() { return MyMaterials::Aluminium(); }},
    {"Cu",    []() { return MyMaterials::Copper(); }},
    {"ESR",   []() { return MyMaterials::ESR_Vikuiti(); }},
    {"Tyvek", []() { return MyMaterials::Tyvek(); }},
    {"PVC",   []() { return MyMaterials::PVC(); }},
    {"PMMA",  []() { return MyMaterials::PMMA(); }},
    {"Quartz",[]() { return MyMaterials::Quartz(); }},
    {"StainlessSteel", []() { return MyMaterials::StainlessSteel(); }},
    {"Air",   []() { return MyMaterials::Air(); }},
    {"Vacuum",[]() { return MyMaterials::Vacuum(); }}
};

G4Material* CompScintSimMaterialFactory::CreateScintillatorMaterial(
    const G4String& materialName, 
    G4double lightYield, 
    G4double resolutionScale, 
    G4double birksConstant)
{
    auto it = scintillatorCreators.find(materialName);
    if (it != scintillatorCreators.end()) {
        return it->second(lightYield, resolutionScale, birksConstant);
    }
    
    // 如果找不到对应材料，抛出异常
    G4ExceptionDescription ed;
    ed << "Unknown scintillator material: " << materialName;
    G4Exception("CompScintSimMaterialFactory::CreateScintillatorMaterial",
                "UnknownMaterial", FatalException, ed);
    return nullptr;
}

G4Material* CompScintSimMaterialFactory::CreateCoatingMaterial(const G4String& materialName)
{
    auto it = coatingCreators.find(materialName);
    if (it != coatingCreators.end()) {
        return it->second();
    }
    
    // 如果找不到对应材料，抛出异常
    G4ExceptionDescription ed;
    ed << "Unknown coating material: " << materialName;
    G4Exception("CompScintSimMaterialFactory::CreateCoatingMaterial",
                "UnknownMaterial", FatalException, ed);
    return nullptr;
}

bool CompScintSimMaterialFactory::IsSupportedScintillatorMaterial(const G4String& materialName)
{
    return scintillatorCreators.find(materialName) != scintillatorCreators.end();
}

bool CompScintSimMaterialFactory::IsSupportedCoatingMaterial(const G4String& materialName)
{
    return coatingCreators.find(materialName) != coatingCreators.end();
} 