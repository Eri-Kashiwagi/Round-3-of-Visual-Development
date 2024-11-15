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

def change(op1, op2):
    try:
        if(op1=="77742"):
            op2=int(op2)+5
        elif(op1=="18078"):
            op2=int(op2)+10
        base_source_path = os.path.join(current_directory, "Python Script Materials\修改Seed和Scenario", f"{op2}")
        source_files = [
            os.path.join(base_source_path, r"AGV运行过程以及其携带的Container\Program.cs"),
            os.path.join(base_source_path, r"计算AGV等待QC装货的数量以及QC目前的状态\Program.cs"),
            os.path.join(base_source_path, r"计算AGV等待YC操作的列表,每个堆场目前堆存Container的数量以及当前堆场YC的状态\Program.cs"),
            os.path.join(base_source_path, r"计算AGV空闲的数量,Delayed以及Waiting船舶数量\Program.cs"),
            os.path.join(base_source_path, r"计算当前泊位停靠的船\Program.cs"),
            os.path.join(base_source_path, r"计算在堆场中每条船待装载的Container的数量\Program.cs"),
            os.path.join(base_source_path, r"计算所有船舶到达时间\Program.cs")
        ]
        target_files = [
            os.path.join(current_directory, r"Calculation_Program\AGV运行过程以及其携带的Container\Program.cs"),
            os.path.join(current_directory, r"Calculation_Program\计算AGV等待QC装货的数量以及QC目前的状态\Program.cs"),
            os.path.join(current_directory, r"Calculation_Program\计算AGV等待YC操作的列表,每个堆场目前堆存Container的数量以及当前堆场YC的状态\Program.cs"),
            os.path.join(current_directory, r"Calculation_Program\计算AGV空闲的数量,Delayed以及Waiting船舶数量\Program.cs"),
            os.path.join(current_directory, r"Calculation_Program\计算当前泊位停靠的船\Program.cs"),
            os.path.join(current_directory, r"Calculation_Program\计算在堆场中每条船待装载的Container的数量\Program.cs"),
            os.path.join(current_directory, r"Calculation_Program\计算所有船舶到达时间\Program.cs")
        ]
        for source, target in zip(source_files, target_files):
            copy_file(source, target)
    except Exception as e:
        print(f"发生错误：{e}")

if __name__ == "__main__":
    print("欢迎使用修改可视化仿真模型Scenario情景脚本")
    print("请选择 Seed (73386, 77742, 18078): ",end='')
    op1 = input().strip()
    print("请选择 Scenario (1-5): ",end='')
    op2 = input().strip()
    print("请确认是否备份完成好并关闭相关程序，本程序启动后将覆盖原文件 (如果完成请输入 1): ",end='')
    op3 = input().strip()
    if op3 == "1":
        if op1 in ["73386", "77742", "18078"] and op2 in ["1", "2", "3", "4", "5"]:
            print(f"执行 Seed {op1}, Scenario {op2} 的操作...")
            change(op1, op2)
            print("任务完成!")
        else:
            print("输入的 Seed 或 Scenario 无效，请检查后重试。")
    else:
        print("操作取消，请备份完成后再运行程序。")
    time.sleep(5)
