import uproot
import matplotlib.pyplot as plt
import numpy as np
import os
import pandas as pd
import math
import csv
from datetime import datetime

class RootData:
    def __init__(self, file_path):
        self.file = uproot.open(file_path)
        self._load_data()
        self.file_path = file_path

    def _validate_indices(self, indices, max_index):
        for index in indices:
            if index < 1 or index > max_index:
                raise ValueError(f"Index {index} out of range. Valid range is 1 to {max_index}.")
            
    def _load_data(self):
        self.Ntuples = {}
        self.H1 = {}
        self.H2 = {}

        # 检查文件结构
        keys = self.file.keys()
        
        # 检查是否有子目录结构
        has_subdirs = any(['histograms' in key or 'ntuples' in key for key in keys])
        
        if has_subdirs:
            # 新的文件结构，带有子目录
            
            # 处理ntuples子目录
            if 'ntuples;1' in keys:
                ntuple_dir = self.file['ntuples']
                ntuple_keys = ntuple_dir.keys()
                
                for i, key in enumerate(ntuple_keys, start=1):
                    ntuple = ntuple_dir[key]
                    try:
                        df = ntuple.arrays(library="pd")
                        self.Ntuples[f'N_{i}'] = df
                    except ValueError as e:
                        print(f"Error loading {key}: {e}")
                        continue
            
            # 处理histograms子目录
            if 'histograms;1' in keys:
                hist_dir = self.file['histograms']
                hist_keys = hist_dir.keys()
                
                # 分类直方图
                h1_keys = []
                h2_keys = []
                
                for key in hist_keys:
                    # 根据直方图类型区分H1和H2
                    hist = hist_dir[key]
                    if 'SourcePosition' in key:  # 假设这是H2类型
                        h2_keys.append(key)
                    else:  # 其他都视为H1类型
                        h1_keys.append(key)
                
                # 加载H1数据
                for i, key in enumerate(h1_keys, start=1):
                    h1 = hist_dir[key]
                    h1_data = h1.to_numpy()
                    h1_values = h1_data[0]
                    h1_edges = h1_data[1]
                    # 使用原始key作为索引，去掉;1后缀
                    clean_key = key.split(';')[0]
                    self.H1[clean_key] = (h1_values, h1_edges)
                
                # 加载H2数据
                for key in h2_keys:
                    h2 = hist_dir[key]
                    try:
                        h2_values = h2.values()
                        h2_edges = np.histogram2d(h2_values[:, 0], h2_values[:, 1])[1:]
                        # 使用原始key作为索引，去掉;1后缀
                        clean_key = key.split(';')[0]
                        self.H2[clean_key] = (h2_values, h2_edges)
                    except Exception as e:
                        print(f"Error loading H2 histogram {key}: {e}")
        else:
            # 旧的文件结构，无子目录
            # 前面若干是Ntuple，后面4个是H1，最后一个是H2
            ntuple_keys = keys[:-5]
            h1_keys = keys[-5:-1]
            h2_key = keys[-1]

            # 加载Ntuple数据
            for i, key in enumerate(ntuple_keys, start=1):
                ntuple = self.file[key]
                try:
                    df = ntuple.arrays(library="pd")
                    self.Ntuples[f'N_{i}'] = df
                except ValueError as e:
                    print(f"Error loading {key}: {e}")
                    continue
            
            # 加载H1数据
            for i, key in enumerate(h1_keys, start=1):
                h1 = self.file[key]
                h1_data = h1.to_numpy()
                h1_values = h1_data[0]
                h1_edges = h1_data[1]
                self.H1[f'H1_{i}'] = (h1_values, h1_edges)

            # 加载H2数据
            h2 = self.file[h2_key]
            h2_values = h2.values()
            h2_edges = np.histogram2d(h2_values[:, 0], h2_values[:, 1])[1:]
            self.H2['H2'] = (h2_values, h2_edges)
        
        # Print 文件基本信息，比如有多少个Ntuples
        # print(f"File contains {len(self.Ntuples)} Ntuples.")
        # print(f"File contains {len(self.H1)} H1 histograms.")
        # print(f"File contains {len(self.H2)} H2 histograms.")
        
    def get_h1_data(self, h1_name):
        return self.H1[h1_name]

    def plot_ntuple(self, indices_to_plot=None):
        if indices_to_plot is None:
            indices_to_plot = range(1, len(self.Ntuples) + 1)
        else:
            self._validate_indices(indices_to_plot, len(self.Ntuples))

        for i in indices_to_plot:
            ntuple_name = f'N_{i}'
            df = self.Ntuples[ntuple_name]
            for column in df.columns:
                plt.figure(figsize=(8, 6))
                plt.hist(df[column], bins=50, alpha=0.7, label=column)
                plt.xlabel(column)
                plt.ylabel("Entries")
                plt.title(f"Histogram of {column} from {ntuple_name}")
                plt.legend()
                plt.show()

    def plot_h1(self):
        num_h1 = len(self.H1)
        if num_h1 == 0:
            print("没有找到H1直方图数据")
            return
            
        # 根据H1数量确定子图布局
        cols = min(4, num_h1)
        rows = (num_h1 + cols - 1) // cols  # 向上取整
        
        fig, axs = plt.subplots(rows, cols, figsize=(cols*4, rows*4))
        if num_h1 == 1:
            axs = np.array([axs])  # 确保axs是数组，便于索引
        
        for i, (h1_name, (values, edges)) in enumerate(self.H1.items()):
            row, col = i // cols, i % cols
            if rows > 1:
                ax = axs[row, col]
            else:
                ax = axs[col]
            
            ax.bar(edges[:-1], values, width=edges[1] - edges[0])
            ax.set_title(h1_name)
        
        # 隐藏未使用的子图
        for i in range(num_h1, rows * cols):
            row, col = i // cols, i % cols
            if rows > 1:
                axs[row, col].set_visible(False)
            else:
                axs[col].set_visible(False)
                
        plt.tight_layout()
        plt.show()

    def plot_h2(self):
        num_h2 = len(self.H2)
        if num_h2 == 0:
            print("没有找到H2直方图数据")
            return
        
        # 根据H2数量确定子图布局
        cols = min(2, num_h2)
        rows = (num_h2 + cols - 1) // cols  # 向上取整
        
        fig, axs = plt.subplots(rows, cols, figsize=(cols*6, rows*5))
        if num_h2 == 1:
            axs = np.array([axs])  # 确保axs是数组，便于索引
        
        for i, (h2_name, (values, edges)) in enumerate(self.H2.items()):
            row, col = i // cols, i % cols
            if rows > 1:
                ax = axs[row, col]
            else:
                ax = axs[col]
            
            im = ax.imshow(values, extent=[edges[0][0], edges[0][-1], edges[1][0], edges[1][-1]], 
                        aspect='auto', origin='lower')
            fig.colorbar(im, ax=ax)
            ax.set_title(h2_name)
            ax.set_xlabel("X axis")
            ax.set_ylabel("Y axis")
        
        # 隐藏未使用的子图
        for i in range(num_h2, rows * cols):
            row, col = i // cols, i % cols
            if rows > 1:
                axs[row, col].set_visible(False)
            else:
                axs[col].set_visible(False)
                
        plt.tight_layout()
        plt.show()

    def save_layers_mean(self, filename):
        # 确保每个文件都有相同的字段
        fields = set()
        for ntuple_name, df in self.Ntuples.items():
            fields.update(df.columns)
        fields = list(fields)

        # 收集每个层的数据
        data = []
        for i, (ntuple_name, df) in enumerate(self.Ntuples.items(), start=1):
            # 尝试从名字中提取层信息
            layer_info = None
            if '_' in ntuple_name:
                parts = ntuple_name.split('_')
                for part in parts:
                    try:
                        layer_info = int(parts[1]) - 1  # 从0开始计数
                        break
                    except ValueError:
                        continue
            
            if layer_info is None:
                layer_info = i - 1  # 默认使用索引作为层数
            
            row = [layer_info]  # 第一列是层数
            for field in fields:
                mean_value = df[field].mean() if field in df.columns else 0
                row.append(mean_value)
            data.append(row)

        # 创建 DataFrame
        columns = ['layers'] + list(fields)
        df = pd.DataFrame(data, columns=columns)
        df.to_csv(filename, index=False)

    def save_simulation_data(self, save_dir, save_name = None):
        """
        根据模拟时间保存特定数据到CSV文件，总共7行数据：
        - 第1-2行：电子能量和计数（只保留计数非0的能量点）
        - 第3-4行：质子能量和计数（同样处理，只保留计数非0的能量点）
        - 第5行：各闪烁体层的能量沉积(energyDeposit)，从Ntuple中获取
        - 第6行：各闪烁体层的NA光子数(FiberNA)，从H1中获取
        - 第7行：各闪烁体层的光纤光子数(FiberEntry)，从H1中获取
        
        参数:
        simulation_time - 模拟的日期和时间，格式为YYMMDDHHMMSS
        """
        # 创建文件名
        if save_name == None:
            save_name = datetime.now().strftime("%Y%m%d%H%M%S")
        
        filename = f"{save_name}.csv"
        
        # 1. 处理电子能谱数据
        electron_energy_dict = {}  # 使用字典存储能量和对应的计数

        if 'N_1' in self.Ntuples:
            df_spectra = self.Ntuples['N_1']
            
            # 查找电子能谱数据
            electron_cols = [col for col in df_spectra.columns if 'electron' in col.lower() or 'e-' in col.lower()]
            if electron_cols:
                electron_col = electron_cols[0]
                # 排除能量为0的粒子
                non_zero_electrons = df_spectra[df_spectra[electron_col] > 0][electron_col]
                
                # 使用字典统计每个能量值出现的次数
                for energy in non_zero_electrons:
                    # 由于浮点数精度问题，可能需要进行取整或保留固定小数位
                    # 这里保留4位小数作为键
                    energy_key = round(energy, 4)
                    if energy_key in electron_energy_dict:
                        electron_energy_dict[energy_key] += 1
                    else:
                        electron_energy_dict[energy_key] = 1
                
                # 转换为排序后的列表，用于后续处理或绘图
                electron_energy = sorted(electron_energy_dict.keys())
                electron_counts = [electron_energy_dict[e] for e in electron_energy]

        # 2. 处理质子能谱数据
        proton_energy_dict = {}  # 使用字典存储能量和对应的计数

        if 'N_1' in self.Ntuples:
            df_spectra = self.Ntuples['N_1']
            
            # 查找质子能谱数据
            proton_cols = [col for col in df_spectra.columns if 'proton' in col.lower() or 'p+' in col.lower()]
            if proton_cols:
                proton_col = proton_cols[0]
                # 排除能量为0的粒子
                non_zero_protons = df_spectra[df_spectra[proton_col] > 0][proton_col]
                
                # 使用字典统计每个能量值出现的次数
                for energy in non_zero_protons:
                    # 保留4位小数作为键
                    energy_key = round(energy, 4)
                    if energy_key in proton_energy_dict:
                        proton_energy_dict[energy_key] += 1
                    else:
                        proton_energy_dict[energy_key] = 1
                
                # 转换为排序后的列表，用于后续处理或绘图
                proton_energy = sorted(proton_energy_dict.keys())
                proton_counts = [proton_energy_dict[e] for e in proton_energy]
        
        # 3. 识别所有可能的层ID
        layer_ids = set()
        import re
        
        # 从H1和Ntuple名称中提取所有可能的层ID
        for h1_name in self.H1.keys():
            h1_name_lower = h1_name.lower()
            if 'layer_' in h1_name_lower:
                layer_match = re.search(r'layer_(\d+)', h1_name_lower)
                if layer_match:
                    layer_id = int(layer_match.group(1))
                    layer_ids.add(layer_id)

        
        # 按层ID排序
        sorted_layer_ids = sorted(layer_ids)
        # 创建层ID到Ntuple的映射
        layer_to_ntuple = {}
        for ntuple_name, df in self.Ntuples.items():
            # 跳过Ntuple_1（能谱数据）
            if ntuple_name == 'N_1':
                continue
            
            # 尝试从名称中提取层ID
            layer_id = None
            if '_' in ntuple_name:
                parts = ntuple_name.split('_')
                for i, part in enumerate(parts):
                    if part.lower() == 'layer' and i+1 < len(parts):
                        try:
                            layer_id = int(parts[i+1])
                            break
                        except ValueError:
                            continue
            
            # 如果找不到层ID，尝试从数字中提取
            if layer_id is None:
                nums = re.findall(r'\d+', ntuple_name)
                if nums:
                    layer_id = int(nums[0])
            
            # 如果找到了层ID，建立映射
            if layer_id is not None:
                # 因为获取到的id是copynumber，是从1开始的。而别的默认是从1开始，所以需要转换
                layer_to_ntuple[layer_id - 1] = ntuple_name
        
        # 初始化数据列表
        energy_deposits = []  # 第5行
        na_photons = []       # 第6行
        fiber_photons = []    # 第7行
        
        # 处理每一层的数据
        for layer_id in sorted_layer_ids:
            # 从Ntuple中获取能量沉积数据（第5行）
            energy_deposit = 0
            if layer_id in layer_to_ntuple:
                ntuple_name = layer_to_ntuple[layer_id ] 
                df = self.Ntuples[ntuple_name]
                # 查找energyDeposit列
                energy_cols = [col for col in df.columns if 'energydeposit' in col.lower()]
                if energy_cols:
                    energy_deposit = df[energy_cols[0]].sum()
            
            # 从H1中获取NA光子数据（第6行）
            na_photon_count = 0
            for h1_name, (values, edges) in self.H1.items():
                h1_name_lower = h1_name.lower()
                if f'layer_{layer_id}_fiberna' in h1_name_lower:
                    na_photon_count = sum(values)
                    break
            
            # 从H1中获取光纤入射光子数据（第7行）
            fiber_photon_count = 0
            for h1_name, (values, edges) in self.H1.items():
                h1_name_lower = h1_name.lower()
                if f'layer_{layer_id}_fiberentry' in h1_name_lower:
                    fiber_photon_count = sum(values)
                    break
            
            # 添加到对应的列表
            energy_deposits.append(energy_deposit)
            na_photons.append(na_photon_count)
            fiber_photons.append(fiber_photon_count)
        
        # 将数据写入CSV文件
        with open(save_dir +'/'+ filename, 'w', newline='') as csvfile:
            writer = csv.writer(csvfile)
            
            # 写入电子数据
            writer.writerow(electron_energy)
            writer.writerow(electron_counts)
            
            # 写入质子数据
            writer.writerow(proton_energy)
            writer.writerow(proton_counts)
            
            # 写入各层数据
            writer.writerow(energy_deposits)  # 第5行：各层能量沉积
            writer.writerow(na_photons)       # 第6行：各层NA光子数
            writer.writerow(fiber_photons)    # 第7行：各层光纤光子数
        
        # print(f"模拟数据已保存至 {filename}")
        return filename

    def save(self, dir_name):
        # 创建文件夹
        base_folder = os.path.splitext(dir_name)[0]
        figure_folder = os.path.join(base_folder, 'figure')
        data_folder = os.path.join(base_folder, 'data')
        os.makedirs(figure_folder, exist_ok=True)
        os.makedirs(data_folder, exist_ok=True)

        # 保存Ntuple数据
        for ntuple_name, df in self.Ntuples.items():
            for column in df.columns:
                file_path = os.path.join(data_folder, f'{ntuple_name}_{column}.csv')
                df[[column]].to_csv(file_path, index=False)

        # 保存层能量均值数据
        mean_data_filename = os.path.join(base_folder, 'layers_mean.csv')
        self.save_layers_mean(mean_data_filename)
        
        # 保存H1数据
        for h1_name, (values, edges) in self.H1.items():
            file_path = os.path.join(data_folder, f'{h1_name}.csv')
            h1_df = pd.DataFrame({'values': values, 'edges': edges[:-1]})
            h1_df.to_csv(file_path, index=False)

        # 保存H2数据
        for h2_name, (values, edges) in self.H2.items():
            h2_df = pd.DataFrame(values)
            h2_df.to_csv(os.path.join(data_folder, f'{h2_name}_values.csv'), index=False)
            np.savetxt(os.path.join(data_folder, f'{h2_name}_edges_x.csv'), edges[0], delimiter=',')
            np.savetxt(os.path.join(data_folder, f'{h2_name}_edges_y.csv'), edges[1], delimiter=',')

        # 保存Ntuple图像
        for ntuple_name, df in self.Ntuples.items():
            for column in df.columns:
                plt.figure(figsize=(8, 6))
                plt.hist(df[column], bins=50, alpha=0.7, label=column)
                plt.xlabel(column)
                plt.ylabel("Entries")
                plt.title(f"Histogram of {column} from {ntuple_name}")
                plt.legend()
                plt.savefig(os.path.join(figure_folder, f'{ntuple_name}_{column}.png'))
                plt.close()

        # 保存H1图像
        for h1_name, (values, edges) in self.H1.items():
            plt.figure(figsize=(8, 6))
            plt.bar(edges[:-1], values, width=edges[1] - edges[0])
            plt.title(h1_name)
            plt.savefig(os.path.join(figure_folder, f'{h1_name}.png'))
            plt.close()

        # 保存H2图像
        for h2_name, (values, edges) in self.H2.items():
            plt.figure(figsize=(8, 6))
            plt.imshow(values, extent=[edges[0][0], edges[0][-1], edges[1][0], edges[1][-1]], aspect='auto', origin='lower')
            plt.colorbar()
            plt.title(h2_name)
            plt.xlabel("X axis")
            plt.ylabel("Y axis")
            plt.savefig(os.path.join(figure_folder, f'{h2_name}.png'))
            plt.close()

