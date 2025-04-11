
# -*- coding: utf-8 -*-

import os
import subprocess
import numpy as np
import argparse
from pathlib import Path

def generate_mac_file(energy, events, output_dir="./mac_files"):
    """生成指定能量和事件数的MAC文件"""
    # 确保输出目录存在
    os.makedirs(output_dir, exist_ok=True)
    
    # 创建MAC文件名（与CSV名相同）
    mac_filename = "e_{:.2f}MeV.mac".format(energy)
    mac_path = os.path.join(output_dir, mac_filename)
    
    # 准备MAC文件内容
    mac_content = """# 基本初始化
/control/verbose 0
/run/verbose 0
/tracking/verbose 0
/control/cout/ignoreThreadsExcept 0
/run/initialize

# 设置输出Root文件名
/MySim/setSaveName e_{:.2f}MeV.csv

# 配置原生Geant4 GPS源
/CompScintSim/generator/useParticleGun false
/gps/source/clear

# 源0: e- @ {:.2f} MeV, 权重 1
/gps/source/add 1
/gps/source/set 0
/gps/particle e-
/gps/ene/type Mono
/gps/energy {:.2f} MeV

# 使用多顶点(基于权重每个事件一个粒子)
/gps/source/multiplevertex false

# 运行模拟
/run/beamOn {}
""".format(energy, energy, energy, events)
    
    # 写入MAC文件
    with open(mac_path, "w") as f:
        f.write(mac_content)
    
    return mac_path

def run_geant4_simulation(mac_file, geant4_executable="./CompScintSim"):
    """运行Geant4模拟"""
    print("正在运行模拟: {}".format(os.path.basename(mac_file)))
    
    # 构建命令
    cmd = [geant4_executable, "-m", mac_file]
    
    # 执行命令
    try:
        result = subprocess.run(cmd, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        print("模拟成功完成: {}".format(os.path.basename(mac_file)))
        return True
    except subprocess.CalledProcessError as e:
        print("模拟失败: {}".format(e))
        print("错误输出: {}".format(e.stderr.decode('utf-8')))
        return False

def main():
    # 创建命令行参数解析器
    parser = argparse.ArgumentParser(description='生成MAC文件并运行Geant4模拟')
    parser.add_argument('--start', type=float, default=0.1, help='能量起始值(MeV)')
    parser.add_argument('--end', type=float, default=2.0, help='能量结束值(MeV)')
    parser.add_argument('--step', type=float, default=0.1, help='能量步长(MeV)')
    parser.add_argument('--events', type=int, default=100000, help='每次模拟的事件数')
    parser.add_argument('--mac_dir', type=str, default='./mac_files', help='MAC文件保存目录')
    parser.add_argument('--geant4_exe', type=str, default='./CompScintSim', help='Geant4可执行文件路径')
    
    args = parser.parse_args()
    
    # 确保MAC文件目录存在
    os.makedirs(args.mac_dir, exist_ok=True)
    
    # 检查Geant4可执行文件是否存在
    geant4_exe = Path(args.geant4_exe)
    if not geant4_exe.exists():
        print("错误: Geant4可执行文件不存在: {}".format(args.geant4_exe))
        return
    
    # 生成能量值列表
    energy_values = np.arange(args.start, args.end + args.step/2, args.step)
    energy_values = [round(e, 2) for e in energy_values]  # 四舍五入到两位小数
    
    print("将生成{}个MAC文件并运行模拟".format(len(energy_values)))
    print("能量范围: {} - {} MeV, 步长: {} MeV".format(args.start, args.end, args.step))
    print("每次模拟事件数: {}".format(args.events))
    
    # 循环处理每个能量值
    for energy in energy_values:
        # 生成MAC文件
        mac_file = generate_mac_file(energy, args.events, args.mac_dir)
        print("已生成MAC文件: {}".format(mac_file))
        
        # 运行Geant4模拟
        success = run_geant4_simulation(mac_file, args.geant4_exe)
        
        if not success:
            print("警告: 能量为 {} MeV 的模拟可能未成功完成".format(energy))
        
        print("-" * 50)
    
    print("所有模拟已完成")

if __name__ == "__main__":
    main()