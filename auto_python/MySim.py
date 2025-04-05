import os,sys
import time
from MacGenerator import EnergySpectrum, MacFileGenerator

current_path = os.path.abspath(os.curdir)
# 把r'../../build' 加入到sys.path中 (确保路径正确)
build_path = os.path.abspath(os.path.join(current_path, r'../build'))
if build_path not in sys.path:
    sys.path.append(build_path)
# 定义相对路径
rel_dir_root = r'./Data/RawData/'  # ROOT files directory
rel_dir_csv  = r'./Data/CSVData/'  # CSV output directory
rel_dir_mac  = r'./Data/MacLog/'   # MAC files directory
rel_dir_log  = r'./Data/RunLog/'   # Simulation log directory
rel_dir_geant4_executable = r'../build/CompScintSim' # Geant4 executable relative path

# 获取绝对路径，末尾加上 '/'. 使用 os.path.normpath 确保路径格式一致
abs_dir_root   = os.path.normpath(os.path.join(current_path, rel_dir_root)) + os.sep
abs_dir_csv    = os.path.normpath(os.path.join(current_path, rel_dir_csv)) + os.sep
abs_dir_mac    = os.path.normpath(os.path.join(current_path, rel_dir_mac)) + os.sep
abs_dir_log    = os.path.normpath(os.path.join(current_path, rel_dir_log)) + os.sep
abs_dir_geant4_executable = os.path.normpath(os.path.join(current_path, rel_dir_geant4_executable))

class MySim:
    """
    Geant4模拟管理类，支持多种配置模式
    """
    def __init__(self, profile=None, spectrum=None, num_events=None, root_file=None, config=None):
        """
        初始化模拟类 (基础构造函数)

        参数：
            profile (str, optional): 模拟配置描述.
            spectrum (EnergySpectrum, optional): 能谱对象.
            num_events (int, optional): 模拟事件数 (run/beamOn).
            root_file (str, optional): Root文件保存路径 (不含扩展名).
            config (dict, optional): 原始配置字典 (用于可能的记录).
        """
        self.config = config or {}
        self.num_events = num_events if num_events is not None else 10 # Default number of events
        self.spectrum = spectrum if spectrum is not None else EnergySpectrum.create_default_spectrum()

        if profile:
            self.run_profile = profile
            self.root_file = root_file if root_file else f"{abs_dir_root}{self.run_profile}"
        elif root_file:
            self.root_file = root_file
            self.run_profile = os.path.basename(root_file).replace('.root', '')
        else:
            # Generate a default profile name if none provided
            timestamp = time.strftime("%Y%m%d_%H%M%S", time.localtime())
            self.run_profile = f"auto_sim_{timestamp}"
            self.root_file = f"{abs_dir_root}{self.run_profile}"

        # 创建MAC文件生成器
        self.mac_generator = MacFileGenerator(
            spectrum=self.spectrum,
            num_events=self.num_events,
            verbose_level=0, # Default verbose level
            root_file=self.root_file # Pass the path without .root extension
        )

    @classmethod
    def from_config(cls, config):
        """
        工厂方法：根据配置字典创建MySim实例

        参数:
            config (dict): 配置字典，包含模式 ('mode') 和相关参数.

        返回:
            MySim: 初始化的模拟对象
        """
        mode = config.get('mode')
        if not mode:
            raise ValueError("配置字典中必须包含 'mode' 键")

        num_events = config.get('num_events', 100) # Use 'num_events' from config, default 100
        if num_events < 100:
             print(f"警告: num_events ({num_events}) 少于推荐值100，可能影响多线程效率。")

        # Generate profile name based on mode and timestamp
        timestamp = time.strftime("%Y%m%d_%H%M%S", time.localtime())
        profile = config.get('profile', f"{mode}_sim_{timestamp}") # Allow custom profile name

        # Generate spectrum based on mode
        spectrum = EnergySpectrum.from_config(config)

        # Create instance
        sim_instance = cls(profile=profile, spectrum=spectrum, num_events=num_events, config=config)

        # Calculate and print total particles
        total_particles_per_event = spectrum.get_total_particles()
        total_simulated_particles = total_particles_per_event * num_events
        print(f"配置 '{profile}':")
        print(f"  模式: {mode}")
        print(f"  每个事件 (event) 包含的总粒子数: {total_particles_per_event}")
        print(f"  模拟事件数 (num_events/beamOn): {num_events}")
        print(f"  总模拟粒子数 (total particles): {total_simulated_particles}")
        print(f"  能谱详情:\n{spectrum}")


        return sim_instance


    @classmethod
    def from_single_particle(cls, particle, energy, number, suffix="", num_events=None):
        """
        (保留) 创建单粒子模拟

        参数：
            particle (str): 粒子类型.
            energy (float): 粒子能量 (MeV).
            number (int): 单次事件中的粒子数量.
            suffix (str, optional): 文件名后缀.
            num_events (int, optional): 模拟事件数, 默认1.

        返回：
            MySim: 初始化的模拟对象
        """
        valid_particles = ["proton", "e-", "e+", "gamma", "neutron", "alpha"]
        if particle not in valid_particles:
            raise ValueError(f"无效的粒子类型：{particle}")

        spectrum = EnergySpectrum()
        spectrum.add_particle(particle, energy, number)

        profile = f"{particle}_{energy}MeV_{number}{suffix}"
        actual_num_events = num_events if num_events is not None else 1

        return cls(profile=profile, spectrum=spectrum, num_events=actual_num_events)

    # Note: from_random_spectrum is now handled by from_config with appropriate config dict

    def get_profile(self):
        """返回模拟配置描述"""
        return self.run_profile

    def write_mac_file(self, dir_mac, mac_name=None):
        """
        生成MAC文件并保存

        参数：
            dir_mac (str): MAC文件保存目录.
            mac_name (str, optional): MAC文件名 (不含路径), 如不指定则使用run_profile.

        返回：
            str: MAC文件完整路径
        """
        if mac_name is None:
            mac_name = f"{self.run_profile}.mac"

        dir_mac_file = os.path.join(dir_mac, mac_name)

        if not os.path.exists(dir_mac):
             # Try creating the directory if it doesn't exist
            try:
                os.makedirs(dir_mac)
                print(f"目录 {dir_mac} 不存在，已自动创建。")
            except OSError as e:
                raise FileNotFoundError(f"无法创建或访问目录：{dir_mac} - {e}")


        # Check for existing file and rename with timestamp if needed
        if os.path.exists(dir_mac_file):
            print(f"警告: MAC文件已存在：{dir_mac_file}")
            current_time = time.localtime()
            timestamp = time.strftime("%H%M%S", current_time)
            original_mac_name = mac_name
            mac_name = f"{os.path.splitext(original_mac_name)[0]}_{timestamp}.mac"
            dir_mac_file = os.path.join(dir_mac, mac_name)
            print(f"自动重命名为：{mac_name}")

        # Generate MAC file using the MacFileGenerator instance
        self.mac_generator.generate_mac_file(dir_mac_file)

        return dir_mac_file 