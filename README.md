

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

1.  **MacGenerator** (`MacGenerator.py`) - 用于根据能谱配置生成 Geant4 宏文件的工具类。
2.  **RootReader** (`RootReader.py`) - 用于读取和处理 Geant4 输出的 ROOT 文件的工具类 (需要 `uproot` 库)。
3.  **MySim** (`MySim.py`) - 模拟配置和运行管理类，负责解析配置、创建能谱、调用 MacGenerator。
4.  **Geant4_BatchDataProc.ipynb** - 主控制脚本，定义模拟配置，调用 MySim 和运行 Geant4 进程。

#### 批处理工作流程

1.  在 `Geant4_BatchDataProc.ipynb` 中定义一个或多个**配置字典 (`config`)**。
2.  每个 `config` 字典指定模拟模式 (`mode`)、粒子参数、事件数 (`num_events`) 等。
3.  调用 `run_batch_simulations(configs, batch_size)` 函数。
4.  脚本内部：
    *   对每个 `config` 和 `batch_size` 中的每一次运行：
        *   调用 `MySim.from_config(config)` 创建模拟实例 (自动生成能谱)。
        *   调用 `sim.write_mac_file()` 生成对应的宏文件 (自动处理文件名和路径)。
        *   调用 `run_geant4()` 函数执行 Geant4 可执行文件，传入生成的宏文件。
    *   自动处理 Geant4 输出 (检查成功/失败，处理 `_t0` 文件，重试)。
    *   (可选) 自动调用 `RootReader` 处理成功的 ROOT 输出文件，将其转换为 CSV 格式存储。

#### 使用配置字典进行批处理

新版本的批处理系统**推荐使用配置字典**来定义模拟任务。以下是一些示例配置：

```python
# 示例：在 Geant4_BatchDataProc.ipynb 中定义配置

# 配置 1: Range Mode (自定义源 /gps/my_source/add)
# 自动在 0.1 到 2.0 MeV (步长 0.2) 范围内生成电子能量点，
# 每个能量点的电子数在 [5, 15] 之间随机抽取。
# 质子类似处理。
config_range = {
    'mode': 'range',             # 模式: 能量范围 + 随机粒子数
    'profile': 'electron_range_sim', # 文件名前缀 (基础)
    'gps_mode': 'custom',        # 使用自定义 /gps/my_source/add
    'num_events': 200,           # Geant4 /run/beamOn 次数

    # 电子配置
    'E_e': [0.1, 2.0],           # 电子能量范围 [min, max] MeV
    'delta_E_e': 0.2,            # 电子能量步长 MeV
    'N_e_once_min': 5,           # 每个能量点单次事件最少电子数
    'N_e_once_max': 15,          # 每个能量点单次事件最多电子数

    # 质子配置 (可选)
    'E_p': [5.0, 10.0],
    'delta_E_p': 1.0,
    'N_p_once_min': 2,
    'N_p_once_max': 8,
}

# 配置 2: Weighted Mode (原生 GPS /gps/source/add)
# 使用 Geant4 原生 GPS，根据权重进行抽样。
# 5.0 MeV 质子权重 1.0, 7.5 MeV 质子权重 2.5, ...
# N_p_once_min 在此模式下仅用于信息打印和内部参考。
config_weighted = {
    'mode': 'weighted',          # 模式: 指定能量点 + 权重
    'profile': 'proton_weighted_sim', # 文件名前缀 (基础)
    'gps_mode': 'native',        # 使用原生 /gps/source/add
    'num_events': 500,           # Geant4 /run/beamOn 次数

    # 质子配置
    'E_p': [5.0, 7.5, 10.0, 12.0], # 质子能量点 (MeV)
    'weights_p': [1.0, 2.5, 3.0, 0.5], # 对应的抽样权重
    'N_p_once_min': 100,         # (参考) *权重最小* (0.5) 的能量点对应的基础粒子数基准

    # 电子配置 (可选)
    'E_e': [0.5, 1.5],
    'weights_e': [2.0, 1.0],
    'N_e_once_min': 50,          # (参考) *权重最小* (1.0) 的能量点对应的基础粒子数基准
}

# 配置 3: Single Particle Mode
config_single = {
    'mode': 'single',
    'profile': 'single_gamma_1MeV',
    'gps_mode': 'custom', # 或 'native' (若为native, 需要 weight > 0)
    'num_events': 1000,
    'particle': 'gamma',
    'energy': 1.0,        # MeV
    'count': 1            # 每个事件产生1个该粒子 (用于 custom mode)
    # 'weight': 1.0       # 如果 gps_mode 是 'native' 则需要此项
}

# 配置 4: 旧版随机能谱模式 (通过嵌套配置)
config_random_legacy = {
    'mode': 'random', # 使用包装器调用旧的随机生成逻辑
    'profile': 'legacy_random_test',
    'gps_mode': 'custom', # 或 'native'
    'num_events': 150,
    'random_config': { # 嵌套旧的随机生成器配置参数
        'e_energy_min': 0.5, 'e_energy_max': 3.0, 'e_delta': 0.5,
        'e_types_min': 2, 'e_types_max': 3,
        'e_count_min': 10, 'e_count_max': 25,
        'p_energy_min': 5.0, 'p_energy_max': 15.0, 'p_delta': 2.0,
        'p_types_min': 1, 'p_types_max': 2,
        'p_count_min': 5, 'p_count_max': 15,
        'use_gamma': False, # 不生成伽马
        # 'nums' is implicitly handled by top-level 'num_events'
    }
}

# 将**所有需要模拟的配置**放入列表
simulation_configs = [
    config_range,
    config_weighted,
    config_single,
    config_random_legacy
]

# 设置每个配置运行的次数
runs_per_config = 5 # 例如，每个配置运行5次

# 运行批量模拟
run_batch_simulations(simulation_configs, runs_per_config)

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


## 代码详细说明

### 几何构建详解

几何构建是Geant4模拟中最基础的部分，在`CompScintSimDetectorConstruction`类中实现。

#### 材料定义

材料定义主要在`MyMaterials()`类中：

- **基础材料**：定义了常用材料如Air、Water、Al、Si等
- **闪烁体材料**：定义了塑料闪烁体(BC-408/BC-412)、无机闪烁体(LYSO/BGO)等
- **光学属性**：定义了材料的折射率、吸收长度、光产额等参数



#### 几何体构建

几何构建在`ConstructGeometry()`方法中：

- **世界体积**：定义了包含所有其他体积的外部空间
- **闪烁体层**：创建多层复合闪烁体结构
- **光探测器**：在闪烁体周围布置光电倍增管或SiPM


#### 光学表面处理

光学表面处理定义了不同材料间界面的光学特性：

- **表面类型**：可设置为抛光(polished)、粗糙(ground)等
- **反射类型**：可设置为漫反射(diffuse)、镜面反射(specular)等
- **表面模型**：可选unified、LUT、DAVIS等模型


### 初级粒子生成器详解

初级粒子生成器在`CompScintSimPrimaryGeneratorAction`类中实现，支持两种模式：

#### ParticleGun模式

这是默认的单粒子源模式，特点：

- 每次事件生成单一类型粒子
- 粒子类型、能量、发射位置、方向可通过宏命令设置
- 适用于单一粒子类型的模拟


#### GPS多粒子源模式

GPS(General Particle Source)提供了更复杂的粒子源配置：

- 支持多种粒子类型同时生成
- 可为每种粒子设置不同的能量谱、空间分布和角分布
- 支持按比例生成不同粒子
- 通过自定义命令`/gps/my_source/add`添加粒子源



### 事件处理详解

事件处理由三个关键类组成：

#### RunAction

`CompScintSimRunAction`类处理整个运行会话：

- **初始化**：在`BeginOfRunAction()`中创建输出文件、初始化数据结构
- **结束处理**：在`EndOfRunAction()`中分析数据、保存结果、关闭文件
- **数据管理**：创建和管理ROOT输出文件


#### EventAction

`CompScintSimEventAction`类处理单个事件：

- **事件初始化**：在`BeginOfEventAction()`中重置事件数据
- **事件处理**：在`EndOfEventAction()`中收集事件数据并填充到输出树中
- **数据汇总**：收集多个步骤产生的能量沉积、光子信息等


#### SteppingAction

`CompScintSimSteppingAction`类处理单个模拟步骤：

- **过程识别**：识别每一步中发生的物理过程（电离、激发、切伦科夫等）
- **数据收集**：收集能量沉积、产生的光子数、相互作用位置等
- **筛选事件**：可根据特定条件筛选感兴趣的事件



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

