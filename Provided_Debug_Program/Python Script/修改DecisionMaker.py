import shutil
import os
import time
current_directory = os.path.dirname(os.getcwd())
def copy_file(source_file, target_path):
    try:
        os.makedirs(os.path.dirname(target_path), exist_ok=True)
        shutil.copy(source_file, target_path)
        print(f"文件 '{os.path.basename(source_file)}' 已成功复制到 '{target_path}' 文件夹中。")
    except FileNotFoundError:
        print(f"未找到源文件：{source_file}")
    except PermissionError:
        print("权限不足，请检查文件和目标文件夹的权限。")
    except Exception as e:
        print(f"发生错误：{e}")

def change():
    try:
        base_source_path = os.path.join(current_directory, r"Python Script Materials\修改DecisionMaker")
        source_file = os.path.join(base_source_path,r"DecisionMaker.cs")
        target_files = [
            os.path.join(current_directory, r"Debug_Program\StrategyMaking\DecisionMaker.cs"),
        ]
        for target in target_files:
            copy_file(source_file, target)
    except Exception as e:
        print(f"发生错误：{e}")

if __name__ == "__main__":
    print("欢迎使用修改DecisionMaker脚本")
    print("请确认是否备份完成好并关闭相关程序，本程序启动后将覆盖原文件 (如果完成请输入 1): ",end='')
    op1 = input().strip()
    change()
    print("任务结束!")
    time.sleep(5)
