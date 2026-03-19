#!/usr/bin/env python3
import os
import re
import shutil

# 获取当前目录
current_dir = os.path.dirname(os.path.abspath(__file__))

# 获取所有cpp文件
cpp_files = [f for f in os.listdir(current_dir) if f.endswith('.cpp')]

# 分类移动文件
for file in cpp_files:
    # 提取文件名开头的数字
    match = re.match(r'^(\d+)', file)
    if match:
        num = int(match.group(1))
        if num < 1000:
            target_dir = os.path.join(current_dir, "0-基础题(0000-0999)")
        elif num < 2000:
            target_dir = os.path.join(current_dir, "1-进阶题(1000-1999)")
        elif num < 3000:
            target_dir = os.path.join(current_dir, "2-提高题(2000-2999)")
        elif num < 4000:
            target_dir = os.path.join(current_dir, "3-高级题(3000-3999)")
        else:
            target_dir = os.path.join(current_dir, "其他")
    else:
        target_dir = os.path.join(current_dir, "其他")
    
    # 移动文件
    source = os.path.join(current_dir, file)
    dest = os.path.join(target_dir, file)
    shutil.move(source, dest)
    print(f"已移动: {file} -> {os.path.basename(target_dir)}")

print(f"\n完成！共整理了 {len(cpp_files)} 个cpp文件")
