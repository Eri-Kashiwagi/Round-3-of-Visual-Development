import os
import time
import pyautogui
import psutil
import subprocess
import threading

current_directory = os.path.dirname(os.getcwd())
solution_file_1 = os.path.join(current_directory, r"Calculation_Program\计算当前泊位停靠的船\WSC_SimChallenge_2024_Net.sln")
solution_file_2 = os.path.join(current_directory, r"Calculation_Program\计算AGV等待QC装货的数量以及QC目前的状态\WSC_SimChallenge_2024_Net.sln")
solution_file_3 = os.path.join(current_directory, r"Calculation_Program\计算AGV等待YC操作的列表,每个堆场目前堆存Container的数量以及当前堆场YC的状态\WSC_SimChallenge_2024_Net.sln")
solution_file_4 = os.path.join(current_directory, r"Calculation_Program\计算AGV空闲的数量,Delayed以及Waiting船舶数量\WSC_SimChallenge_2024_Net.sln")
solution_file_5 = os.path.join(current_directory, r"Calculation_Program\AGV运行过程以及其携带的Container\WSC_SimChallenge_2024_Net.sln")
solution_file_6 = os.path.join(current_directory, r"Calculation_Program\计算在堆场中每条船待装载的Container的数量\WSC_SimChallenge_2024_Net.sln")
solution_file_7 = os.path.join(current_directory, r"Calculation_Program\计算所有船舶到达时间\WSC_SimChallenge_2024_Net.sln.sln")
solution_file_8 = os.path.join(current_directory, r"Visualization_program\可视化开发_round3版本\港口可视化开发.sln")

def open_solution_with_default_program(solution_file):
    try:
        os.startfile(solution_file)
        print(f"解决方案文件 {solution_file} 已打开")
    except FileNotFoundError:
        print(f"无法找到文件：{solution_file}")
    except Exception as e:
        print(f"打开文件时出错: {e}")

def run_solution():
    time.sleep(12) 
    print("准备运行项目...")
    pyautogui.press('f5') 

def get_debugging_process(process_name, start_time):
    for proc in psutil.process_iter(['pid', 'name', 'create_time']):
        if proc.info['name'] == process_name and proc.info['create_time'] >= start_time:
            print(f"找到调试进程: {proc.info['name']} (PID: {proc.info['pid']})")
            return proc
    return None

def wait_for_debugging_process(process_name, start_time, timeout=60):
    print(f"正在等待调试进程 {process_name} 启动...")
    elapsed_time = 0
    while elapsed_time < timeout:
        debug_proc = get_debugging_process(process_name, start_time)
        if debug_proc:
            print(f"调试进程 {process_name} 已启动 (PID: {debug_proc.info['pid']})")
            return debug_proc
        time.sleep(2)
        elapsed_time += 2
    print(f"超时: 未能找到调试进程 {process_name}")
    return None

def monitor_debugging_process(debug_proc, event):
    print(f"开始监控调试进程 (PID: {debug_proc.pid})...")
    try:
        while debug_proc.is_running():
            print(f"调试进程 (PID: {debug_proc.pid}) 正在运行...")
            time.sleep(5)
        print(f"调试进程 (PID: {debug_proc.pid}) 已退出，该部分数据采集完成。")
        event.set() 

    except psutil.NoSuchProcess:
        print(f"进程 (PID: {debug_proc.pid}) 已不存在，可能已崩溃。")
        event.set() 

def close_visual_studio():
    try:
        subprocess.run(["taskkill", "/IM", "devenv.exe", "/F"], check=True)
        print("Visual Studio 已关闭")
    except subprocess.CalledProcessError as e:
        print(f"关闭 Visual Studio 时出错: {e}")

def run_and_monitor_solution(solution_file, process_name, event):
    start_time = time.time()
    open_solution_with_default_program(solution_file)
    run_solution()
    debug_proc = wait_for_debugging_process(process_name, start_time)
    if debug_proc:
        monitor_debugging_process(debug_proc, event)

if __name__ == "__main__":
    event_1 = threading.Event()
    event_2 = threading.Event()
    event_3 = threading.Event()
    thread_1 = threading.Thread(target=run_and_monitor_solution, args=(solution_file_1, "WSC_SimChallenge_2024_Net.exe", event_1))
    thread_2 = threading.Thread(target=run_and_monitor_solution, args=(solution_file_2, "WSC_SimChallenge_2024_Net.exe", event_2))
    thread_3 = threading.Thread(target=run_and_monitor_solution, args=(solution_file_3, "WSC_SimChallenge_2024_Net.exe", event_3))
    thread_1.start()
    time.sleep(40) 
    thread_2.start()
    time.sleep(40)
    thread_3.start()
    event_1.wait()
    event_2.wait()
    event_3.wait()
    close_visual_studio()
    time.sleep(5)
    event_4 = threading.Event()
    event_5 = threading.Event()
    event_6 = threading.Event()
    thread_4 = threading.Thread(target=run_and_monitor_solution, args=(solution_file_4, "WSC_SimChallenge_2024_Net.exe", event_4))
    thread_5 = threading.Thread(target=run_and_monitor_solution, args=(solution_file_5, "WSC_SimChallenge_2024_Net.exe", event_5))
    thread_6 = threading.Thread(target=run_and_monitor_solution, args=(solution_file_6, "WSC_SimChallenge_2024_Net.exe", event_6))
    thread_4.start()
    time.sleep(40)
    thread_5.start()
    time.sleep(40)
    thread_6.start()
    event_4.wait()
    event_5.wait()
    event_6.wait()
    close_visual_studio()
    time.sleep(5)
    event_7 = threading.Event()
    thread_7 = threading.Thread(target=run_and_monitor_solution, args=(solution_file_7, "WSC_SimChallenge_2024_Net.exe", event_7))
    close_visual_studio()
    print("已完成数据采集，开始可视化仿真")
    time.sleep(5)
    event_8 = threading.Event()
    thread_8 =threading.Thread(target=run_and_monitor_solution, args=(solution_file_8, "WSC_SimChallenge_2024_Net.exe", event_8))
    thread_8.start()
