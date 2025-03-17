import numpy as np
import random

# 全局变量：控制能量值保留的小数位数
ENERGY_DECIMAL_PLACES = 2

class Particle:
    """
    表示一种具有特定能量和数量的粒子
    
    属性:
        type (str): 粒子类型 (如 'e-', 'proton', 'gamma' 等)
        energy (float): 粒子能量，单位MeV
        count (int): 该能量下的粒子数量
    """
    
    def __init__(self, particle_type, energy, count):
        """
        初始化粒子
        
        参数:
            particle_type (str): 粒子类型 (如 'e-' 或 'proton')
            energy (float): 粒子能量 (MeV)
            count (int): 粒子数量
        """
        self.type = particle_type
        # 根据全局小数位数控制变量对能量值进行四舍五入
        self.energy = round(float(energy), ENERGY_DECIMAL_PLACES)
        self.count = int(count)
    
    def __str__(self):
        """返回粒子的描述字符串"""
        return f"{self.count}个 {self.energy}MeV {self.type}"
    
    def mac_command(self):
        """返回该粒子的MAC文件命令"""
        return f"/gps/my_source/add {self.type} {self.energy} MeV {self.count}"


class EnergySpectrum:
    """
    表示完整的辐射场能谱，包含多种不同类型和能量的粒子
    
    属性:
        particles (list): 包含所有Particle对象的列表
    """
    
    def __init__(self):
        """初始化空能谱"""
        self.particles = []
    
    def add_particle(self, particle_type, energy, count):
        """
        添加一种粒子到能谱中
        
        参数:
            particle_type (str): 粒子类型 ('e-', 'proton', 'gamma'等)
            energy (float): 粒子能量 (MeV)
            count (int): 粒子数量
        """
        self.particles.append(Particle(particle_type, energy, count))
        return self  # 支持链式调用
    
    def clear(self):
        """清空能谱中的所有粒子"""
        self.particles = []
        return self  # 支持链式调用
    
    def get_total_particles(self):
        """获取能谱中的总粒子数"""
        return sum(p.count for p in self.particles)
    
    def __str__(self):
        """返回能谱的描述字符串"""
        return "\n".join(str(p) for p in self.particles)
    
    @classmethod
    def create_default_spectrum(cls):
        """
        创建默认能谱: 10个1MeV电子、5个5MeV质子、20个1MeV伽马
        
        返回:
            EnergySpectrum: 包含默认粒子配置的能谱对象
        """
        spectrum = cls()
        spectrum.add_particle("e-", 1.0, 10)
        spectrum.add_particle("proton", 5.0, 5)
        spectrum.add_particle("gamma", 1.0, 20)
        return spectrum
    
    @classmethod
    def generate_random_spectrum(cls, config=None):
        """
        根据规则自动生成随机能谱
        
        参数:
            config (dict, optional): 配置字典，包含随机生成的各种参数
                                     如果为None，则使用默认配置
        
        返回:
            EnergySpectrum: 随机生成的能谱对象
        """
        spectrum = cls()
        
        # 默认配置
        default_config = {
            'use_manual': False,  # 是否使用手动配置
            
            # 手动配置
            'manual_e_energies': [1.0],     # 电子能量 (MeV)
            'manual_e_counts': [10],        # 电子数量
            'manual_p_energies': [5.0],     # 质子能量 (MeV)
            'manual_p_counts': [5],         # 质子数量
            'manual_g_energies': [1.0],     # 伽马能量 (MeV)
            'manual_g_counts': [20],        # 伽马数量
            
            # 自动生成配置 - 电子
            'e_energy_min': 0.3,            # 电子能量最小值 (MeV)
            'e_energy_max': 2.0,            # 电子能量最大值 (MeV)
            'e_delta': 0.1,                 # 电子能量间隔 (MeV)
            'e_types_min': 1,               # 电子能量种类数下限
            'e_types_max': 2,               # 电子能量种类数上限
            'e_count_min': 5,               # 每种电子最小数量
            'e_count_max': 20,              # 每种电子最大数量
            
            # 自动生成配置 - 质子
            'p_energy_min': 5.0,            # 质子能量最小值 (MeV)
            'p_energy_max': 20.0,           # 质子能量最大值 (MeV)
            'p_delta': 0.1,                 # 质子能量间隔 (MeV)
            'p_types_min': 1,               # 质子能量种类数下限
            'p_types_max': 2,               # 质子能量种类数上限
            'p_count_min': 5,               # 每种质子最小数量
            'p_count_max': 20,              # 每种质子最大数量
            
            # 自动生成配置 - 伽马
            'g_energy_min': 0.5,            # 伽马能量最小值 (MeV)
            'g_energy_max': 3.0,            # 伽马能量最大值 (MeV)
            'g_delta': 0.1,                 # 伽马能量间隔 (MeV)
            'g_types_min': 1,               # 伽马能量种类数下限
            'g_types_max': 2,               # 伽马能量种类数上限
            'g_count_min': 5,               # 每种伽马最小数量
            'g_count_max': 30,              # 每种伽马最大数量
            
            # 各种粒子是否启用
            'use_electron': True,           # 是否使用电子
            'use_proton': True,             # 是否使用质子
            'use_gamma': True,              # 是否使用伽马
            
            # 模拟事件参数
            'nums': 10,                     # run/beamOn 命令的事件数
            
            # 其他参数
            'random_types': True,           # 是否随机化粒子种类数
        }
        
        # 合并用户配置和默认配置
        if config is None:
            config = default_config
        else:
            for key, value in default_config.items():
                if key not in config:
                    config[key] = value
        
        if config['use_manual']:
            # 手动配置模式
            
            # 添加电子
            if config['use_electron']:
                for i, energy in enumerate(config['manual_e_energies']):
                    if i < len(config['manual_e_counts']) and config['manual_e_counts'][i] > 0:
                        spectrum.add_particle("e-", energy, config['manual_e_counts'][i])
            
            # 添加质子
            if config['use_proton']:
                for i, energy in enumerate(config['manual_p_energies']):
                    if i < len(config['manual_p_counts']) and config['manual_p_counts'][i] > 0:
                        spectrum.add_particle("proton", energy, config['manual_p_counts'][i])
            
            # 添加伽马
            if config['use_gamma']:
                for i, energy in enumerate(config['manual_g_energies']):
                    if i < len(config['manual_g_counts']) and config['manual_g_counts'][i] > 0:
                        spectrum.add_particle("gamma", energy, config['manual_g_counts'][i])
        
        else:
            # 自动生成模式
            
            # 生成可选的电子能量数组
            if config['use_electron']:
                e_options = np.arange(config['e_energy_min'], 
                                     config['e_energy_max'] + config['e_delta'], 
                                     config['e_delta'])
                # 对能量值进行四舍五入，确保符合小数位数要求
                e_options = [round(e, ENERGY_DECIMAL_PLACES) for e in e_options]
                # 去除可能的重复值
                e_options = list(set(e_options))
                
                # 决定本次使用的电子能量种类数
                if config['random_types']:
                    # 确保种类数在min和max之间
                    n_e_selected = random.randint(
                        min(config['e_types_min'], len(e_options)),
                        min(config['e_types_max'], len(e_options))
                    )
                else:
                    n_e_selected = min(config['e_types_max'], len(e_options))
                
                # 确保至少使用最小种类数（如果有足够的可选能量）
                n_e_selected = max(n_e_selected, min(config['e_types_min'], len(e_options)))
                
                # 随机选择电子能量
                if n_e_selected > 0:
                    e_selected = random.sample(e_options, n_e_selected)
                    
                    # 为每种电子能量分配数量
                    for energy in e_selected:
                        count = random.randint(config['e_count_min'], config['e_count_max'])
                        spectrum.add_particle("e-", energy, count)
            
            # 生成可选的质子能量数组
            if config['use_proton']:
                p_options = np.arange(config['p_energy_min'], 
                                     config['p_energy_max'] + config['p_delta'], 
                                     config['p_delta'])
                # 对能量值进行四舍五入，确保符合小数位数要求
                p_options = [round(p, ENERGY_DECIMAL_PLACES) for p in p_options]
                # 去除可能的重复值
                p_options = list(set(p_options))
                
                # 决定本次使用的质子能量种类数
                if config['random_types']:
                    # 确保种类数在min和max之间
                    n_p_selected = random.randint(
                        min(config['p_types_min'], len(p_options)),
                        min(config['p_types_max'], len(p_options))
                    )
                else:
                    n_p_selected = min(config['p_types_max'], len(p_options))
                
                # 确保至少使用最小种类数（如果有足够的可选能量）
                n_p_selected = max(n_p_selected, min(config['p_types_min'], len(p_options)))
                
                # 随机选择质子能量
                if n_p_selected > 0:
                    p_selected = random.sample(p_options, n_p_selected)
                    
                    # 为每种质子能量分配数量
                    for energy in p_selected:
                        count = random.randint(config['p_count_min'], config['p_count_max'])
                        spectrum.add_particle("proton", energy, count)
            
            # 生成可选的伽马能量数组
            if config['use_gamma']:
                g_options = np.arange(config['g_energy_min'], 
                                     config['g_energy_max'] + config['g_delta'], 
                                     config['g_delta'])
                # 对能量值进行四舍五入，确保符合小数位数要求
                g_options = [round(g, ENERGY_DECIMAL_PLACES) for g in g_options]
                # 去除可能的重复值
                g_options = list(set(g_options))
                
                # 决定本次使用的伽马能量种类数
                if config['random_types']:
                    # 确保种类数在min和max之间
                    n_g_selected = random.randint(
                        min(config['g_types_min'], len(g_options)),
                        min(config['g_types_max'], len(g_options))
                    )
                else:
                    n_g_selected = min(config['g_types_max'], len(g_options))
                
                # 确保至少使用最小种类数（如果有足够的可选能量）
                n_g_selected = max(n_g_selected, min(config['g_types_min'], len(g_options)))
                
                # 随机选择伽马能量
                if n_g_selected > 0:
                    g_selected = random.sample(g_options, n_g_selected)
                    
                    # 为每种伽马能量分配数量
                    for energy in g_selected:
                        count = random.randint(config['g_count_min'], config['g_count_max'])
                        spectrum.add_particle("gamma", energy, count)
        
        return spectrum, config['nums']  # 返回能谱和事件数


class MacFileGenerator:
    """
    生成Geant4 MAC文件的类
    
    属性:
        spectrum (EnergySpectrum): 能谱对象
        num_events (int): 模拟事件数
        verbose_level (int): 详细输出级别 (0-2)
        root_file (str): Root文件保存路径
    """
    
    def __init__(self, spectrum=None, num_events=10, verbose_level=0, root_file=None):
        """
        初始化MAC文件生成器
        
        参数:
            spectrum (EnergySpectrum, optional): 能谱对象，如果为None则创建默认能谱
            num_events (int, optional): 模拟事件数，默认为10
            verbose_level (int, optional): 详细输出级别，默认为0
            root_file (str, optional): Root文件保存路径
        """
        self.spectrum = spectrum if spectrum is not None else EnergySpectrum.create_default_spectrum()
        self.num_events = num_events
        self.verbose_level = verbose_level
        self.root_file = root_file
    
    def generate_mac_file(self, output_path="radiation_field.mac"):
        """
        生成MAC文件
        
        参数:
            output_path (str, optional): 输出文件路径，默认为"radiation_field.mac"
            
        返回:
            str: 生成的MAC文件内容
        """
        # 创建MAC文件内容
        mac_content = f"""# 自定义GPS多粒子源宏文件

# 基本初始化
/control/verbose {self.verbose_level}
/run/verbose {self.verbose_level}
/tracking/verbose {self.verbose_level}
/control/cout/ignoreThreadsExcept 0
/run/initialize

# 设置输出文件路径
"""
        if self.root_file:
            mac_content += f"/MySim/setSaveName {self.root_file}\n\n"
        
        mac_content += """# 禁用默认的ParticleGun
/CompScintSim/generator/useParticleGun false

# 清除所有已定义的GPS源
/gps/my_source/clear

# 添加多个粒子源
"""
        
        # 添加每种粒子的源配置
        for particle in self.spectrum.particles:
            mac_content += f"{particle.mac_command()}\n"
        
        # 添加列出源和运行命令
        mac_content += """
# 列出所有定义的源
/gps/my_source/list

# 生成事件（单次事件释放所有粒子）
"""
        mac_content += f"/run/beamOn {self.num_events}\n"
        
        # 写入文件
        with open(output_path, "w") as f:
            f.write(mac_content)
        
        # print(f"MAC文件已创建: {output_path}")
        return mac_content

# 设置能量值保留的小数位数
def set_energy_decimal_places(decimal_places):
    """
    设置能量值保留的小数位数
    
    参数:
        decimal_places (int): 要保留的小数位数，必须是非负整数
    """
    global ENERGY_DECIMAL_PLACES
    if decimal_places < 0:
        raise ValueError("小数位数必须是非负整数")
    ENERGY_DECIMAL_PLACES = decimal_places
    print(f"能量值将保留 {ENERGY_DECIMAL_PLACES} 位小数")