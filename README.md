# CompositeScintillatorSim

## 项目介绍

CompositeScintillatorSim 是一个基于 Geant4 的复合闪烁体模拟项目，用于研究各种粒子与复合闪烁体材料的相互作用过程。该项目支持单粒子和多粒子源的模拟，并提供批处理功能以实现大规模模拟工作。

## 功能特点

- 支持多种粒子类型：电子、质子、伽马射线等
- 支持单粒子源和多粒子源配置
- 提供批处理自动化脚本，可生成自定义能谱和随机能谱
- 自动保存模拟结果并可导出为CSV格式
- 故障自动重试机制，确保模拟稳定性
- 支持GDML导入几何构建（需编译时启用）

## 项目结构

```
CompositeScintillatorSim/
├── include/                  # 头文件目录
├── src/                      # 源代码目录
├── build/                    # 编译后的可执行文件
├── mac/                      # 宏文件目录
│   ├── multi_particle.mac    # 多粒子源示例宏文件
│   ├── single_particle.mac   # 单粒子源示例宏文件
│   └── ...
├── auto_python/              # 自动化脚本
│   ├── Geant4_BatchDataProc.ipynb  # 批处理脚本
│   ├── MacGenerator.py       # 宏文件生成器
│   ├── RootReader.py         # ROOT文件读取工具
│   └── Data/                 # 存放模拟数据
│       ├── RawData/          # 原始ROOT文件
│       ├── CSVData/          # 转换后的CSV文件
│       ├── MacLog/           # 宏文件备份
│       └── RunLog/           # 运行日志
└── ...
```

## 核心组件说明

### 几何构建

项目使用 `CompScintSimDetectorConstruction` 类构建复合闪烁体几何结构。主要包括：

- 闪烁体材料定义（光学特性、密度等）
- 几何体构建（形状、尺寸、位置）
- 光学表面处理

如需修改几何结构，请编辑 `src/CompScintSimDetectorConstruction.cc` 文件。

### 初级粒子产生器

粒子产生由 `CompScintSimPrimaryGeneratorAction` 类负责，支持两种模式：

1. **ParticleGun 模式**：单一粒子源，可通过宏文件配置粒子类型、能量等
2. **GPS 多粒子源模式**：可配置多种粒子类型、能量和数量的混合源

相关文件：`src/CompScintSimPrimaryGeneratorAction.cc`

### 事件处理

核心事件处理组件包括：

- **RunAction**：处理整个运行会话，负责初始化和结束时的操作
- **EventAction**：处理单个事件，收集每个事件中的能量沉积信息
- **SteppingAction**：处理单个模拟步骤，收集每一步的物理过程信息

## Quick Start

### 编译项目

```bash
# 创建并进入build目录
mkdir -p build
cd build

# 配置CMake
cmake ..

# 编译项目
make -j4  # 使用4个核心编译

# 回到项目根目录
cd ..
```

### 运行模拟

#### GUI交互式运行

```bash
# 启动带有图形界面的模拟
./build/CompScintSim
```

#### 使用宏文件运行

```bash
# 使用单粒子源宏文件
./build/CompScintSim -m mac/single_particle.mac

# 使用多粒子源宏文件
./build/CompScintSim -m mac/multi_particle.mac

# 使用自定义随机数种子
./build/CompScintSim -m mac/single_particle.mac -r 12345

# 启用调试模式（显示详细信息）
./build/CompScintSim -m mac/single_particle.mac -debug
```

#### 使用GDML导入几何（如果支持）

```bash
# 使用GDML文件定义几何
./build/CompScintSim -g geometry.gdml -m mac/single_particle.mac
```

#### 多线程运行（如果支持）

```bash
# 使用4个线程运行
./build/CompScintSim -m mac/single_particle.mac -t 4
```

## 使用方法

### 单次模拟

可以通过编写宏文件进行单次模拟。以下提供两种常用的宏文件模板：

#### 单粒子源示例 (single_particle.mac)

```
/control/verbose 0
/tracking/verbose 0
/run/verbose 0
/control/cout/ignoreThreadsExcept 0

/run/initialize
/CompScintSim/generator/useParticleGun true

/MySim/setSaveName test

# 设置初级粒子为电子
/gun/particle e-

# 设置每次粒子的能量
/gun/energy 1.0 MeV

# 设置运行次数
/run/beamOn 100
```

#### 多粒子源示例 (multi_particle.mac)

```
# 基本初始化
/control/verbose 0
/run/verbose 0
/tracking/verbose 0
/run/initialize

# 禁用默认的ParticleGun
/CompScintSim/generator/useParticleGun false

# 清除所有已定义的GPS源
/gps/my_source/clear

# 添加多个自定义粒子源
/gps/my_source/add e- 1.0 MeV 10
/gps/my_source/add proton 5.0 MeV 5
/gps/my_source/add gamma 1 MeV 20

# 列出所有定义的源
/gps/my_source/list

# 生成事件（100次事件）
/run/beamOn 100
```

### 批处理模拟

项目提供了批处理脚本 `auto_python/Geant4_BatchDataProc.ipynb`，可以自动生成宏文件并运行多次模拟。批处理系统包含以下主要组件：

1. **MacGenerator** - 用于生成宏文件的工具类
2. **RootReader** - 用于处理ROOT输出文件的工具类
3. **MySim** - 模拟配置和运行管理类

#### 批处理工作流程

1. 创建模拟配置（自定义或随机能谱）
2. 生成对应的宏文件
3. 调用Geant4可执行文件运行模拟
4. 自动处理输出的ROOT文件
5. 将结果转换为CSV格式存储

#### 使用自定义能谱示例

```python
# 创建能谱
custom_spectrum = EnergySpectrum()
custom_spectrum.add_particle("e-", 1.5, 20)  # 电子，1.5 MeV，20个
custom_spectrum.add_particle("proton", 10.0, 5)  # 质子，10.0 MeV，5个

# 创建模拟
sim = MySim(profile="custom_sim", spectrum=custom_spectrum, num_events=200)

# 写入MAC文件并运行模拟
mac_file = sim.write_mac_file()
run_geant4(abs_dir_geant4, mac_file, "custom_sim_log")
```

#### 使用随机能谱示例

```python
# 配置随机能谱参数
config = {
    'e_types_min': 2,      # 至少2种电子能量
    'e_energy_min': 0.5,   # 电子能量范围0.5-3.0 MeV
    'e_energy_max': 3.0,
    'p_types_min': 2,
    'p_types_max': 3,
    'nums': 200,           # 每次模拟的事件数
    'use_gamma': False     # 不使用gamma
}

# 创建随机能谱模拟
sim = MySim.from_random_spectrum(config, profile="random_spectrum_test")
mac_file = sim.write_mac_file()
run_geant4(abs_dir_geant4, mac_file, "random_sim_log")
```

## 模拟结果处理

模拟结果保存为ROOT文件，可以使用 `RootData` 类将其转换为CSV格式：

```python
# 处理ROOT文件
root_data = RootData(root_file_path)
# 保存为CSV
csv_path = root_data.save_simulation_data(abs_dir_csv, csv_filename)
```

## 注意事项

1. 运行前请确保已正确编译Geant4程序
2. 宏文件路径应使用相对路径或绝对路径
3. 批处理脚本会自动创建必要的目录结构
4. 如果模拟失败，系统会自动重试（最多3次）

## 常见问题

1. **模拟结果中包含 `_t0` 文件**：这表明模拟过程中出现了问题，批处理系统会自动删除这些文件并重试
2. **ROOT文件未生成**：检查日志文件了解详细错误信息
3. **批处理脚本运行缓慢**：可以适当减少事件数量或粒子类型来提高运行速度

## TODO 列表

- [ ] 添加更多材料的光学特性参数
- [ ] 实现更复杂的几何结构配置
- [ ] 增加对能量谱分析的可视化支持
- [ ] 优化多线程性能
- [ ] 添加更多样本宏文件
- [ ] 实现配置文件驱动的模拟（无需修改源代码）
- [ ] 添加单元测试
- [ ] 改进文档和用户指南

## 代码详细说明

### 几何构建详解

几何构建是Geant4模拟中最基础的部分，在`CompScintSimDetectorConstruction`类中实现。

#### 材料定义

材料定义主要在`DefineMaterials()`方法中：

- **基础材料**：定义了常用材料如Air、Water、Al、Si等
- **闪烁体材料**：定义了塑料闪烁体(BC-408/BC-412)、无机闪烁体(LYSO/BGO)等
- **光学属性**：定义了材料的折射率、吸收长度、光产额等参数

```cpp
// 材料光学属性定义示例
G4MaterialPropertiesTable* mptPlScin = new G4MaterialPropertiesTable();
mptPlScin->AddProperty("RINDEX", photonEnergy, refractiveIndex, nEntries);
mptPlScin->AddProperty("ABSLENGTH", photonEnergy, absLength, nEntries);
mptPlScin->AddProperty("FASTCOMPONENT", photonEnergy, scintilFast, nEntries);
```

#### 几何体构建

几何构建在`ConstructGeometry()`方法中：

- **世界体积**：定义了包含所有其他体积的外部空间
- **闪烁体层**：创建多层复合闪烁体结构
- **光探测器**：在闪烁体周围布置光电倍增管或SiPM

```cpp
// 创建闪烁体逻辑体积示例
G4Box* solidScintillator = new G4Box("Scintillator", 
                                    scintX/2, scintY/2, scintZ/2);
G4LogicalVolume* logicScintillator = 
    new G4LogicalVolume(solidScintillator, scintillatorMaterial, "Scintillator");
```

#### 光学表面处理

光学表面处理定义了不同材料间界面的光学特性：

- **表面类型**：可设置为抛光(polished)、粗糙(ground)等
- **反射类型**：可设置为漫反射(diffuse)、镜面反射(specular)等
- **表面模型**：可选unified、LUT、DAVIS等模型

```cpp
// 光学表面处理示例
G4OpticalSurface* opticalSurface = new G4OpticalSurface("Surface");
opticalSurface->SetType(dielectric_dielectric);
opticalSurface->SetFinish(polished);
opticalSurface->SetModel(unified);
```

### 初级粒子生成器详解

初级粒子生成器在`CompScintSimPrimaryGeneratorAction`类中实现，支持两种模式：

#### ParticleGun模式

这是默认的单粒子源模式，特点：

- 每次事件生成单一类型粒子
- 粒子类型、能量、发射位置、方向可通过宏命令设置
- 适用于单一粒子类型的模拟

```cpp
// ParticleGun模式关键代码
G4ParticleGun* particleGun = new G4ParticleGun(1);
particleGun->SetParticleDefinition(particle);
particleGun->SetParticleEnergy(energy);
particleGun->SetParticlePosition(position);
particleGun->SetParticleMomentumDirection(momentumDirection);
```

#### GPS多粒子源模式

GPS(General Particle Source)提供了更复杂的粒子源配置：

- 支持多种粒子类型同时生成
- 可为每种粒子设置不同的能量谱、空间分布和角分布
- 支持按比例生成不同粒子
- 通过自定义命令`/gps/my_source/add`添加粒子源

```cpp
// GPS多粒子源关键实现
void AddParticleSource(G4String particleName, G4double energy, G4int number) {
    // 创建粒子定义
    G4ParticleDefinition* particle = 
        G4ParticleTable::GetParticleTable()->FindParticle(particleName);
    
    // 添加到源列表
    ParticleSource source;
    source.particle = particle;
    source.energy = energy;
    source.number = number;
    fParticleSources.push_back(source);
}
```

### 事件处理详解

事件处理由三个关键类组成：

#### RunAction

`CompScintSimRunAction`类处理整个运行会话：

- **初始化**：在`BeginOfRunAction()`中创建输出文件、初始化数据结构
- **结束处理**：在`EndOfRunAction()`中分析数据、保存结果、关闭文件
- **数据管理**：创建和管理ROOT输出文件

```cpp
// RunAction关键方法
void CompScintSimRunAction::BeginOfRunAction(const G4Run* run) {
    // 创建ROOT文件
    fRootFile = new TFile(fOutputFileName, "RECREATE");
    // 创建树结构
    fEventTree = new TTree("Events", "Simulation Events Data");
    // 添加分支
    fEventTree->Branch("EventID", &fEventID, "EventID/I");
    // ...其他分支
}
```

#### EventAction

`CompScintSimEventAction`类处理单个事件：

- **事件初始化**：在`BeginOfEventAction()`中重置事件数据
- **事件处理**：在`EndOfEventAction()`中收集事件数据并填充到输出树中
- **数据汇总**：收集多个步骤产生的能量沉积、光子信息等

```cpp
// EventAction关键方法
void CompScintSimEventAction::EndOfEventAction(const G4Event* event) {
    // 汇总事件数据
    fRunAction->SetEventData(fEventID, fEdepTotal, fScintPhotons, fCerenPhotons);
    // 填充事件树
    fRunAction->FillEventTree();
}
```

#### SteppingAction

`CompScintSimSteppingAction`类处理单个模拟步骤：

- **过程识别**：识别每一步中发生的物理过程（电离、激发、切伦科夫等）
- **数据收集**：收集能量沉积、产生的光子数、相互作用位置等
- **筛选事件**：可根据特定条件筛选感兴趣的事件

```cpp
// SteppingAction关键方法
void CompScintSimSteppingAction::UserSteppingAction(const G4Step* step) {
    // 获取能量沉积
    G4double edep = step->GetTotalEnergyDeposit();
    if (edep > 0) {
        fEventAction->AddEdep(edep);
    }
    
    // 检测产生的光子
    const G4TrackVector* secondaries = step->GetSecondary();
    for (size_t i = 0; i < secondaries->size(); i++) {
        G4Track* secTrack = (*secondaries)[i];
        // 检查是否为光子
        if (secTrack->GetDefinition() == G4OpticalPhoton::Definition()) {
            // 识别产生过程
            G4String processName = secTrack->GetCreatorProcess()->GetProcessName();
            if (processName == "Scintillation") {
                fEventAction->IncrementScintPhotons();
            } else if (processName == "Cerenkov") {
                fEventAction->IncrementCerenPhotons();
            }
        }
    }
}
```

### 自定义命令

项目实现了多个自定义命令，扩展了Geant4的默认功能：

#### 粒子生成器命令

在`CompScintSimGeneratorMessenger`类中：

- `/CompScintSim/generator/useParticleGun [true/false]`：切换ParticleGun和GPS模式
- `/gps/my_source/add [particle] [energy] [number]`：添加自定义粒子源
- `/gps/my_source/clear`：清除已定义的所有粒子源
- `/gps/my_source/list`：列出当前定义的所有粒子源

#### 数据保存命令

在`CompScintSimRunActionMessenger`类中：

- `/MySim/setSaveName [name]`：设置输出文件名
- `/MySim/setRootPath [path]`：设置ROOT文件保存路径
- `/MySim/enableOpticalData [true/false]`：是否保存光学过程数据

### 物理过程设置

使用`G4VModularPhysicsList`实现物理过程设置：

- **标准电磁过程**：使用G4EmStandardPhysics_option4提供更精确的电磁相互作用
- **强相互作用过程**：使用FTFP_BERT强子物理模型
- **光学过程**：使用G4OpticalPhysics提供光学光子的产生、传播和探测

```cpp
// 物理过程设置示例
G4VModularPhysicsList* physicsList = new FTFP_BERT;
physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());
G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
physicsList->RegisterPhysics(opticalPhysics);
```

