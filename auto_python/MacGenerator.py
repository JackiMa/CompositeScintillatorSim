import numpy as np
import random
import math # Import math for ceil
import os
import logging

# 禁用该模块中的默认控制台输出处理器
for handler in logging.root.handlers[:]:
    logging.root.removeHandler(handler)
logging.getLogger().addHandler(logging.NullHandler())

# 全局变量：控制能量值保留的小数位数
ENERGY_DECIMAL_PLACES = 2

class Particle:
    """
    表示一种具有特定能量和数量的粒子
    
    属性:
        type (str): 粒子类型 (如 'e-', 'proton', 'gamma' 等)
        energy (float): 粒子能量，单位MeV
        count (int): 该能量下的粒子数量 (在自定义源模式下表示单次event释放数量)
        weight (float, optional): 抽样权重 (在原生GPS模式下使用)，默认为None
    """
    
    def __init__(self, particle_type, energy, count, weight=None):
        """
        初始化粒子
        
        参数:
            particle_type (str): 粒子类型 (如 'e-' 或 'proton')
            energy (float): 粒子能量 (MeV)
            count (int): 粒子数量 (用于自定义源或基于权重的计算)
            weight (float, optional): 抽样权重 (用于原生GPS模式)
        """
        self.type = particle_type
        # 根据全局小数位数控制变量对能量值进行四舍五入
        self.energy = round(float(energy), ENERGY_DECIMAL_PLACES)
        self.count = int(count)
        self.weight = weight
    
    def __str__(self):
        """返回粒子的描述字符串"""
        if self.weight is not None:
             # Primarily for weighted mode description
             return f"类型: {self.type}, 能量: {self.energy} MeV, 权重: {self.weight} (对应计数: {self.count})"
        else:
             # Primarily for range/custom mode description
             return f"类型: {self.type}, 能量: {self.energy} MeV, 数量/事件: {self.count}"
    
    def mac_command_custom(self):
        """返回该粒子的自定义MAC文件命令 (/gps/my_source/add)"""
        # Count here represents particles per event for the custom source
        if self.count <= 0:
            return None # Don't add commands for zero count
        return f"/gps/my_source/add {self.type} {self.energy} MeV {self.count}"

    def mac_command_native(self, index):
        """返回该粒子的原生GPS MAC文件命令 (/gps/source/...)"""
        # Weight is used for native GPS sampling
        if self.weight is None or self.weight <= 0:
             print(f"警告: 粒子 {self.type} @ {self.energy} MeV 缺少有效权重，将跳过原生GPS命令生成。")
             return None # Skip if weight is not valid for native mode

        commands = []
        # Use weight for /gps/source/add
        commands.append(f"/gps/source/add {self.weight}")
        commands.append(f"/gps/source/set {index}") # Use the provided index
        commands.append(f"/gps/particle {self.type}")
        commands.append(f"/gps/ene/type Mono")
        commands.append(f"/gps/energy {self.energy} MeV")
        return "\n".join(commands)


class EnergySpectrum:
    """
    表示完整的辐射场能谱，包含多种不同类型和能量的粒子
    
    属性:
        particles (list): 包含所有Particle对象的列表
        gps_mode (str): 生成MAC文件时使用的GPS模式 ('custom' 或 'native')
    """
    
    def __init__(self, gps_mode='custom'): # Default to custom mode
        """初始化空能谱"""
        self.particles = []
        self.gps_mode = gps_mode # Store the intended GPS mode
    
    def add_particle(self, particle_type, energy, count, weight=None):
        """
        添加一种粒子到能谱中
        
        参数:
            particle_type (str): 粒子类型 ('e-', 'proton', 'gamma'等)
            energy (float): 粒子能量 (MeV)
            count (int): 粒子数量 (用于自定义源或基于权重的计算)
            weight (float, optional): 抽样权重 (用于原生GPS模式)
        """
        # Check for duplicates (same type and energy) and merge if found
        merged = False
        for p in self.particles:
            if p.type == particle_type and p.energy == round(float(energy), ENERGY_DECIMAL_PLACES):
                p.count += int(count) # Sum counts
                # Decide how to handle weights on merge - sum? average? overwrite?
                # For now, let's assume the new weight overwrites or is ignored if None
                if weight is not None:
                    p.weight = weight # Or perhaps sum weights: p.weight = (p.weight or 0) + weight
                merged = True
                break
        if not merged:
            self.particles.append(Particle(particle_type, energy, count, weight))

        return self  # 支持链式调用
    
    def clear(self):
        """清空能谱中的所有粒子"""
        self.particles = []
        return self  # 支持链式调用
    
    def get_total_particles(self):
        """获取能谱中的总粒子数 (基于count，代表自定义源模式下的单事件粒子数)"""
        # This reflects the number of particles released *per event* in the 'custom' source mode
        # For 'native' GPS mode, the total number depends on beamOn and weights, this value isn't directly comparable.
        return sum(p.count for p in self.particles)
    
    def __str__(self):
        """返回能谱的描述字符串"""
        if not self.particles:
            return "空能谱"
        # Sort particles by type, then energy for consistent output
        sorted_particles = sorted(self.particles, key=lambda p: (p.type, p.energy))
        return "\n".join(f"  - {p}" for p in sorted_particles)
    
    @classmethod
    def create_default_spectrum(cls, gps_mode='custom'):
        """
        创建默认能谱: 10个1MeV电子、5个5MeV质子、20个1MeV伽马
        
        返回:
            EnergySpectrum: 包含默认粒子配置的能谱对象
        """
        spectrum = cls(gps_mode=gps_mode) # Pass mode
        spectrum.add_particle("e-", 1.0, 10, weight=1.0) # Assign default weight
        spectrum.add_particle("proton", 5.0, 5, weight=0.5)
        spectrum.add_particle("gamma", 1.0, 20, weight=2.0)
        return spectrum
    
    @classmethod
    def from_config(cls, config):
        """
        工厂方法：根据配置字典创建能谱实例
        
        参数:
            config (dict): 配置字典
        
        返回:
            EnergySpectrum: 根据配置生成的能谱对象
        """
        mode = config.get('mode')
        if not mode:
            raise ValueError("配置字典 'config' 必须包含 'mode' 键")

        # Determine GPS mode from config, default to 'custom'
        # Weighted mode implies native GPS, others default to custom unless specified
        gps_mode = config.get('gps_mode', 'native' if mode == 'weighted' else 'custom')
        spectrum = cls(gps_mode=gps_mode) # Initialize with the determined mode

        particle_configs = {
            'e': ('e-', 'E_e', 'delta_E_e', 'N_e_once_min', 'N_e_once_max', 'weights_e'),
            'p': ('proton', 'E_p', 'delta_E_p', 'N_p_once_min', 'N_p_once_max', 'weights_p'),
            'g': ('gamma', 'E_g', 'delta_E_g', 'N_g_once_min', 'N_g_once_max', 'weights_g')
            # Add other particle types here if needed
        }

        if mode == 'range':
            for p_code, (p_type, E_key, delta_key, N_min_key, N_max_key, _) in particle_configs.items():
                if E_key in config and delta_key in config and N_min_key in config and N_max_key in config:
                    E_range = config[E_key]
                    delta_E = config[delta_key]
                    N_min = config[N_min_key]
                    N_max = config[N_max_key]

                    if not isinstance(E_range, (list, tuple)) or len(E_range) != 2:
                        raise ValueError(f"配置错误: '{E_key}' 必须是包含两个元素的列表或元组 [min, max]")
                    if delta_E <= 0:
                         raise ValueError(f"配置错误: '{delta_key}' 必须是正数")
                    if N_min < 0 or N_max < N_min:
                         raise ValueError(f"配置错误: '{N_min_key}' 和 '{N_max_key}' 必须是非负数且 min <= max")


                    # Generate energy points, adding delta_E/2 to include the endpoint potentially
                    energies = np.arange(E_range[0], E_range[1] + delta_E / 2.0, delta_E)
                    energies = [round(e, ENERGY_DECIMAL_PLACES) for e in energies]
                    energies = sorted(list(set(energies))) # Ensure unique and sorted

                    if not energies:
                        print(f"警告: 无法在范围 {E_range} (步长 {delta_E}) 内为粒子 {p_type} 生成能量点。")
                        continue

                    for energy in energies:
                        # Randomly sample count for this energy point
                        count = random.randint(N_min, N_max)
                        if count > 0:
                            # Weight is not directly used in custom mode but can be set for potential future use or consistency
                            spectrum.add_particle(p_type, energy, count, weight=count) # Use count as weight placeholder?

        elif mode == 'weighted':
             total_min_weight_contribution = 0 # Track the total particle count contribution from the minimum weight entries

             for p_code, (p_type, E_key, _, N_min_key, _, weights_key) in particle_configs.items():
                 if E_key in config and weights_key in config and N_min_key in config:
                    energies = config[E_key]
                    weights = config[weights_key]
                    N_min_for_min_weight = config[N_min_key] # Count corresponding to the minimum weight

                    if not isinstance(energies, (list, tuple)) or not isinstance(weights, (list, tuple)):
                         raise ValueError(f"配置错误: '{E_key}' 和 '{weights_key}' 必须是列表或元组")
                    if len(energies) != len(weights):
                        raise ValueError(f"配置错误: '{E_key}' ({len(energies)} 项) 和 '{weights_key}' ({len(weights)} 项) 的长度必须匹配")
                    if N_min_for_min_weight <= 0:
                         raise ValueError(f"配置错误: '{N_min_key}' 必须是正整数")


                    if not weights:
                        print(f"警告: 粒子 {p_type} 的权重列表为空，跳过。")
                        continue

                    valid_weights = [w for w in weights if w > 0]
                    if not valid_weights:
                        raise ValueError(f"配置错误: 粒子 {p_type} 的 '{weights_key}' 中必须至少包含一个正权重")

                    min_weight = min(valid_weights)
                    total_min_weight_contribution += N_min_for_min_weight # Add the base count for this particle type


                    for energy, weight in zip(energies, weights):
                        if weight > 0:
                             # Calculate count based on weight relative to min_weight
                             # The count represents the number of particles if the simulation ran enough times
                             # for the minimum weight particle to appear N_min_for_min_weight times.
                             count = int(round(N_min_for_min_weight * weight / min_weight))
                             count = max(count, 1) # Ensure at least 1 particle even for very small weights relative to min

                             # Add particle with its energy, calculated count, and original weight
                             spectrum.add_particle(p_type, energy, count, weight=weight)
                         # else: Ignore entries with non-positive weights


             # Calculate suggested num_events for weighted mode
             # if total_min_weight_contribution > 0 and gps_mode == 'native':
                 # This calculation seems complex and potentially confusing based on the user request.
                 # Let's stick to the user's formula: num_events = N_min_for_min_weight * total_energy_points / min_global_weight ?
                 # The user request is ambiguous: "N_e_once_min * length of E_e / min(weights)" - applies per particle type? globally?
                 # Let's calculate a suggestion based on ensuring the minimum weight particle appears roughly N_min_for_min_weight times *per particle type*
                 # This still doesn't give a single num_events easily.
                 # Revisit the calculation: Maybe num_events should just be set directly in config?
                 # Let's use the user-provided num_events or a default. The printout in MySim already shows total particles.
                 # pass # Keep num_events as set in MySim.from_config - This pass is unnecessary and can be removed
                 # Calculation is now handled externally by calculate_native_beam_on


        elif mode == 'random':
             # Delegate to the existing random generator
             # Ensure the config dictionary is compatible or adapt it
             random_config = config.get('random_config', {}) # Allow nesting random params
             # Merge top-level params like 'num_events' if they aren't in random_config
             if 'num_events' not in random_config and 'num_events' in config:
                 random_config['num_events'] = config['num_events']

             # The generate_random_spectrum returns spectrum and num_events, we only need spectrum here
             # Note: generate_random_spectrum needs update to accept gps_mode and set weights
             generated_spectrum, _ = EnergySpectrum.generate_random_spectrum(random_config, gps_mode=gps_mode)
             spectrum.particles = generated_spectrum.particles # Transfer particles
             spectrum.gps_mode = generated_spectrum.gps_mode # Transfer mode

        # Add other modes like 'single' if needed, reusing MySim.from_single_particle logic
        elif mode == 'single':
             p_type = config.get('particle')
             energy = config.get('energy')
             count = config.get('count', 1) # Particles per event
             if not p_type or energy is None:
                 raise ValueError("配置错误: 'single' 模式需要 'particle' 和 'energy' 参数")
             spectrum.add_particle(p_type, energy, count, weight=count) # Use count as weight placeholder

        else:
            raise ValueError(f"未知的能谱生成模式: '{mode}'")

        return spectrum


    @classmethod
    def generate_random_spectrum(cls, config=None, gps_mode='custom'): # Added gps_mode
        """
        根据规则自动生成随机能谱
        (Modified to accept gps_mode and potentially set weights)
        
        参数:
            config (dict, optional): 配置字典
            gps_mode (str): GPS模式 ('custom' or 'native')
        
        返回:
            (EnergySpectrum, int): (随机生成的能谱对象, 事件数)
        """
        # spectrum = cls() # Original init
        spectrum = cls(gps_mode=gps_mode) # Initialize with mode

        # ... (rest of the default config and logic remains largely the same)
        # --- Omitted for brevity, assume default_config is defined as before ---
        default_config = {
            'use_manual': False,
            'manual_e_energies': [1.0], 'manual_e_counts': [10],
            'manual_p_energies': [5.0], 'manual_p_counts': [5],
            'manual_g_energies': [1.0], 'manual_g_counts': [20],
            'e_energy_min': 0.3, 'e_energy_max': 2.0, 'e_delta': 0.1,
            'e_types_min': 1, 'e_types_max': 2, 'e_count_min': 5, 'e_count_max': 20,
            'p_energy_min': 5.0, 'p_energy_max': 20.0, 'p_delta': 0.1,
            'p_types_min': 1, 'p_types_max': 2, 'p_count_min': 5, 'p_count_max': 20,
            'g_energy_min': 0.5, 'g_energy_max': 3.0, 'g_delta': 0.1,
            'g_types_min': 1, 'g_types_max': 2, 'g_count_min': 5, 'g_count_max': 30,
            'use_electron': True, 'use_proton': True, 'use_gamma': True,
            'nums': 10, # Note: Renamed to num_events elsewhere, keep consistent
            'random_types': True,
        }
        if config is None: config = default_config
        else: default_config.update(config); config = default_config
        num_events = config.get('nums', config.get('num_events', 10)) # Handle both keys


        if config['use_manual']:
            # 手动配置模式
            if config['use_electron']:
                for i, energy in enumerate(config['manual_e_energies']):
                     if i < len(config['manual_e_counts']) and config['manual_e_counts'][i] > 0:
                         count = config['manual_e_counts'][i]
                         spectrum.add_particle("e-", energy, count, weight=count) # Set weight = count
            if config['use_proton']:
                 for i, energy in enumerate(config['manual_p_energies']):
                     if i < len(config['manual_p_counts']) and config['manual_p_counts'][i] > 0:
                         count = config['manual_p_counts'][i]
                         spectrum.add_particle("proton", energy, count, weight=count) # Set weight = count
            if config['use_gamma']:
                 for i, energy in enumerate(config['manual_g_energies']):
                     if i < len(config['manual_g_counts']) and config['manual_g_counts'][i] > 0:
                         count = config['manual_g_counts'][i]
                         spectrum.add_particle("gamma", energy, count, weight=count) # Set weight = count
        else:
            # 自动生成模式
            particle_params = [
                ('e-', config['use_electron'], config['e_energy_min'], config['e_energy_max'], config['e_delta'], config['e_types_min'], config['e_types_max'], config['e_count_min'], config['e_count_max']),
                ('proton', config['use_proton'], config['p_energy_min'], config['p_energy_max'], config['p_delta'], config['p_types_min'], config['p_types_max'], config['p_count_min'], config['p_count_max']),
                ('gamma', config['use_gamma'], config['g_energy_min'], config['g_energy_max'], config['g_delta'], config['g_types_min'], config['g_types_max'], config['g_count_min'], config['g_count_max'])
            ]

            for p_type, use_flag, en_min, en_max, delta, t_min, t_max, c_min, c_max in particle_params:
                 if use_flag:
                     options = np.arange(en_min, en_max + delta / 2.0, delta)
                     options = [round(e, ENERGY_DECIMAL_PLACES) for e in options]
                     options = sorted(list(set(options)))

                     if not options: continue # Skip if no energy options generated

                     # Determine number of types
                     n_selected = 0
                     if len(options) > 0:
                         min_types = min(t_min, len(options))
                         max_types = min(t_max, len(options))
                         if config['random_types']:
                             n_selected = random.randint(min_types, max_types)
                         else:
                             n_selected = max_types
                         n_selected = max(n_selected, min_types) # Ensure minimum if possible


                     # Select energies and counts
                     if n_selected > 0:
                         selected_energies = random.sample(options, n_selected)
                         for energy in selected_energies:
                             count = random.randint(c_min, c_max)
                             if count > 0:
                                 spectrum.add_particle(p_type, energy, count, weight=count) # Set weight = count


        # return spectrum, config['nums'] # Original
        return spectrum, num_events

    @staticmethod
    def calculate_native_beam_on(config):
        """
        计算原生加权模式下建议的 /run/beamOn 值，
        基于确保最低权重的粒子达到其 N_min 计数。

        参数:
            config (dict): 模拟配置字典。

        返回:
            int: 计算出的事件数 (beamOn 值)。
                 如果不是原生加权模式或无法计算，则返回配置中原始的 'num_events'。
        """
        mode = config.get('mode')
        gps_mode = config.get('gps_mode', 'native' if mode == 'weighted' else 'custom')

        if not (mode == 'weighted' and gps_mode == 'native'):
            # 如果不是目标模式，则返回现有的 num_events
            return config.get('num_events', 100) # 如果未指定，默认为 100

        particle_configs = {
            # particle code: (Energy key, Weights key, N_min_key)
            'e': ('E_e', 'weights_e', 'N_e_once_min'),
            'p': ('E_p', 'weights_p', 'N_p_once_min'),
            'g': ('E_g', 'weights_g', 'N_g_once_min')
        }

        required_events_list = []

        for p_code, (E_key, weights_key, N_min_key) in particle_configs.items():
            # 检查该粒子类型所需的所有键是否存在于配置中
            if E_key in config and weights_key in config and N_min_key in config:
                weights = config[weights_key]
                N_min_for_min_weight = config[N_min_key]

                # 验证权重列表和 N_min 值
                if not isinstance(weights, (list, tuple)) or not weights or N_min_for_min_weight <= 0:
                    logging.warning(f"跳过 {p_code} 的 beamOn 计算：权重列表无效或 N_min_key ({N_min_key}) 无效。")
                    continue

                # 筛选出有效的正权重值
                valid_weights = [w for w in weights if isinstance(w, (int, float)) and w > 0]
                if not valid_weights:
                    logging.warning(f"跳过 {p_code} 的 beamOn 计算：未找到有效的正权重。")
                    continue

                min_weight = min(valid_weights)
                sum_weights = sum(valid_weights)

                # 根据公式计算所需的事件数： N_min * sum(weights) / min(weight)
                # 使用 math.ceil 确保向上取整，保证最低权重粒子至少达到 N_min 次
                try:
                     calculated_events = math.ceil(N_min_for_min_weight * sum_weights / min_weight)
                     required_events_list.append(calculated_events)
                     logging.debug(f"计算 {p_code}: N_min={N_min_for_min_weight}, sum_w={sum_weights}, min_w={min_weight} -> events={calculated_events}")
                except ZeroDivisionError:
                     logging.warning(f"跳过 {p_code} 的 beamOn 计算：最低权重为零。")
                except Exception as e:
                    logging.warning(f"计算 {p_code} 的 beamOn 时出错：{e}")

        # 如果没有任何粒子类型能成功计算出所需事件数
        if not required_events_list:
             logging.warning("原生加权模式：无法从任何粒子类型计算所需的事件数。将使用配置中的 num_events。")
             return config.get('num_events', 100) # 使用配置值或默认值作为后备

        # 最终的 num_events 取所有粒子类型计算结果中的最大值
        calculated_base_events = max(required_events_list)
        logging.info(f"计算得到原生加权模式的基础 num_events: {calculated_base_events} (基于 N_min 和权重)")

        # --- 新增：应用 scale_factor --- 
        scale_factor = config.get('scale_factor', 1) # 从配置读取，默认为1
        final_num_events = calculated_base_events # 默认最终值等于基础值

        if isinstance(scale_factor, int) and scale_factor >= 1:
            if scale_factor > 1:
                # 生成 1 到 scale_factor 之间的随机整数
                random_factor = random.uniform(1, scale_factor)
                final_num_events = calculated_base_events * random_factor
                final_num_events = int(final_num_events)
                logging.info(f"应用随机缩放因子: {random_factor} (范围 [1, {scale_factor}])")
                logging.info(f"最终计算得到的 num_events: {final_num_events}")
            # else: 如果 scale_factor == 1, 无需操作，final_num_events 已是基础值
        else:
            logging.warning(f"配置中的 scale_factor ('{scale_factor}') 无效，应为 >= 1 的整数。将忽略缩放因子。")
            # 此时 final_num_events 仍然是 calculated_base_events
        # ------------------------------

        return final_num_events


class MacFileGenerator:
    """
    生成Geant4 MAC文件的类
    
    属性:
        spectrum (EnergySpectrum): 能谱对象
        num_events (int): 模拟事件数 (run/beamOn)
        verbose_level (int): 详细输出级别 (0-2)
        root_file (str): Root文件保存路径 (不含扩展名)
        gps_mode (str): 使用的GPS命令模式 ('custom' 或 'native')
    """
    
    def __init__(self, spectrum, num_events=10, verbose_level=0, root_file=None):
        """
        初始化MAC文件生成器
        
        参数:
            spectrum (EnergySpectrum): 能谱对象 (必须提供)
            num_events (int, optional): 模拟事件数，默认为10
            verbose_level (int, optional): 详细输出级别，默认为0
            root_file (str, optional): Root文件保存路径 (不含扩展名)
        """
        if spectrum is None:
            raise ValueError("MacFileGenerator 需要一个 EnergySpectrum 对象")

        self.spectrum = spectrum
        self.num_events = num_events
        self.verbose_level = verbose_level
        self.root_file = root_file # Path without extension
        self.gps_mode = spectrum.gps_mode # Inherit mode from spectrum
    
    def generate_mac_file(self, output_path="radiation_field.mac"):
        """
        生成MAC文件
        
        参数:
            output_path (str): 输出文件路径
        
        返回:
            str: 生成的MAC文件内容
        """
        # --- Base MAC Content ---
        mac_content = f"""# Geant4 MAC file generated by MacFileGenerator
# GPS Mode: {self.gps_mode}
# Profile: {os.path.basename(output_path).replace('.mac','')}

# Basic Initialization
/control/verbose {self.verbose_level}
/run/verbose {self.verbose_level}
/tracking/verbose {self.verbose_level}
/control/cout/ignoreThreadsExcept 0
/run/initialize

# Set Output Root File Name (if provided)
"""
        if self.root_file:
            # Ensure it's just the name, not the full path if not intended
            # The /MySim/setSaveName command in C++ likely handles the directory
            # root_file_basename = os.path.basename(self.root_file) # Incorrect assumption - Remove basename extraction
            # mac_content += f"/MySim/setSaveName {root_file_basename}\n\n" # Use just the name part
            # Correction: Pass the full path (without extension) stored in self.root_file
            mac_content += f"/MySim/setSaveName {self.root_file}\n\n"
        else:
            mac_content += "# Warning: Output root file name not set.\n\n"


        # --- GPS Configuration based on mode ---
        if self.gps_mode == 'native':
            mac_content += "# Configuring Native Geant4 GPS Sources\n"
            mac_content += "/CompScintSim/generator/useParticleGun false\n" # Ensure custom gun is off
            mac_content += "/gps/source/clear\n\n" # Clear previous sources

            source_index = 0
            for particle in self.spectrum.particles:
                native_cmd = particle.mac_command_native(source_index)
                if native_cmd:
                    mac_content += f"# Source {source_index}: {particle.type} @ {particle.energy} MeV, Weight {particle.weight}\n"
                    mac_content += native_cmd + "\n\n"
                    source_index += 1

            if source_index == 0:
                 mac_content += "# Warning: No valid sources defined for native GPS mode.\n"

            mac_content += "# Use multiple vertices (one particle per event based on weights)\n"
            mac_content += "/gps/source/multiplevertex false\n\n" # As per user example

        elif self.gps_mode == 'custom':
            mac_content += "# Configuring Custom Multi-Particle Source\n"
            mac_content += "/CompScintSim/generator/useParticleGun false\n" # Ensure particle gun is off (redundant?)
            mac_content += "/gps/my_source/clear\n\n" # Clear custom source

            mac_content += "# Add particle definitions to custom source\n"
            commands_added = 0
            for particle in self.spectrum.particles:
                custom_cmd = particle.mac_command_custom()
                if custom_cmd:
                    mac_content += custom_cmd + "\n"
                    commands_added +=1

            if commands_added == 0:
                 mac_content += "# Warning: No particles added to the custom source.\n"

            mac_content += "\n# List the defined custom sources (for verification)\n"
            mac_content += "/gps/my_source/list\n\n"

        else:
            mac_content += "# ERROR: Unknown gps_mode '{self.gps_mode}'\n"


        # --- Run Command ---
        mac_content += "# Run the simulation\n"
        mac_content += f"/run/beamOn {self.num_events}\n"

        # Write to file
        try:
            with open(output_path, "w") as f:
                f.write(mac_content)
            # print(f"MAC文件已创建: {output_path} (模式: {self.gps_mode})")
        except IOError as e:
            print(f"错误: 无法写入MAC文件 {output_path}: {e}")
            # Handle error appropriately, maybe raise it again
            raise

        return mac_content

# 设置能量值保留的小数位数
def set_energy_decimal_places(decimal_places):
    """
    设置能量值保留的小数位数
    
    参数:
        decimal_places (int): 要保留的小数位数，必须是非负整数
    """
    global ENERGY_DECIMAL_PLACES
    if not isinstance(decimal_places, int) or decimal_places < 0:
        raise ValueError("小数位数必须是非负整数")
    ENERGY_DECIMAL_PLACES = decimal_places
    logging.info(f"能量值将保留 {ENERGY_DECIMAL_PLACES} 位小数")