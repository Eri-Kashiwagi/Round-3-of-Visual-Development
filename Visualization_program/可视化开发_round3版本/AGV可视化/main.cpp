#include <iostream>
#include <fstream>   
#include <graphics.h> 
#include <cmath>     
#include <ctime>    
#include <vector>
#include <ctime> 
#include <sstream> 
#include <iomanip>
#include<mmsystem.h>
#include <windows.h>
#include <shlwapi.h>
#include <thread>
#include "tools.h"    
#include "vector2.h"  
#include "AGV_operation_and_its_container.h"
#include "QCLocation.h"
#include "AGV_waitlist_container_count_per_yard_Status.h"
#include "AGV_waitlist_QC_Status.h"
#include "YBLocation.h"
#include "YB_Vessel_Num.h"
#include "ClockTime.h"
#include "AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum.h"
#include "Berth_Vessel.h"
#include "Directory.h"
#include"Change_Speed.h"
#pragma comment(lib, "winmm.lib")  
using namespace std;
AGV_operation_and_its_container Agv_operation_and_its_container;
QCLocation Qclocation;
AGV_waitlist_container_count_per_yard_Status Agv_waitlist_container_count_per_yard_Status;
AGV_waitlist_QC_Status Agv_waitlist_QC_Status;
YBLocation Yblocation;
ClockTime Clocktime;
YB_Vessel_Num Yb_Vessel_Num;
AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum Agv_BeingIdleNum_Vessel_DelayedNum_WaitingNum;
Berth_Vessel berth_Vessel;
Change_Speed change_speed;
IMAGE bg;
IMAGE PLAYPNG;
IMAGE HALTPNG;
IMAGE sea;
IMAGE Road;
IMAGE hasten;
IMAGE decelerate;
IMAGE decelerate1;
IMAGE hasten1;
int TimeMax = 6048000;
int oneday = 86400;
int ld=0,lf=0;
long long op, l;
class visualization {
public:
    static void update();
    static void stop();
    static bool stopflag;
};
bool visualization::stopflag = false;
void visualization::stop() {
    if (MouseHit()) {
        ExMessage msg = getmessage();
        if (msg.message == WM_LBUTTONDOWN) {
            if (msg.x >= 770 && msg.x <= 870 && msg.y >= 848 + 22 && msg.y <= 952 + 22) {
                if (stopflag == false)stopflag = true;
                else stopflag = false;
            }
        }
        if (stopflag == true) {
            change_speed.change(msg);
            if (msg.message == WM_LBUTTONDOWN) {
                if (msg.x >= 768 && msg.x <= 818 && msg.y >= 647 && msg.y <= 717) {
                    putimage(768, 647, &decelerate1);
                    ld = 0;
                    lf--;
                    std::thread t1(&AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum::unzip_use_file, &Agv_BeingIdleNum_Vessel_DelayedNum_WaitingNum, lf);
                    std::thread t2(&AGV_operation_and_its_container::unzip_use_file, &Agv_operation_and_its_container, lf);
                    std::thread t3(&AGV_waitlist_container_count_per_yard_Status::unzip_use_file, &Agv_waitlist_container_count_per_yard_Status, lf);
                    std::thread t4(&AGV_waitlist_QC_Status::unzip_use_file, &Agv_waitlist_QC_Status, lf);
                    std::thread t5(&Berth_Vessel::unzip_use_file, &berth_Vessel, lf);
                    std::thread t6(&YB_Vessel_Num::unzip_use_file, &Yb_Vessel_Num, lf);
                    std::thread t7(&AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum::unzip_file, &Agv_BeingIdleNum_Vessel_DelayedNum_WaitingNum, lf);
                    std::thread t8(&AGV_operation_and_its_container::unzip_file, &Agv_operation_and_its_container, lf);
                    std::thread t9(&AGV_waitlist_container_count_per_yard_Status::unzip_file, &Agv_waitlist_container_count_per_yard_Status, lf);
                    std::thread t10(&AGV_waitlist_QC_Status::unzip_file, &Agv_waitlist_QC_Status, lf);
                    std::thread t11(&Berth_Vessel::unzip_file, &berth_Vessel, lf);
                    std::thread t12(&YB_Vessel_Num::unzip_file, &Yb_Vessel_Num, lf);
                    t1.join();
                    t2.join();
                    t3.join();
                    t4.join();
                    t5.join();
                    t6.join();
                    t7.detach();
                    t8.detach();
                    t9.detach();
                    t10.detach();
                    t11.detach();
                    t12.detach();
                    ClockTime temp;
                    time_t userTimeT = std::mktime(&temp.userTime);
                    time_t newTimeT = userTimeT + (lf-1)* oneday;
                    Clocktime.update(difftime(newTimeT,Clocktime.current_time_t),0,0);
                    putimage(768, 647, &decelerate);
                }
                else if (msg.x >= 823 && msg.x <= 873 && msg.y >= 647 && msg.y <= 717) {
                    putimage(823, 647, &hasten1);
                    ld = 0;
                    lf++;
                    std::thread t1(&AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum::unzip_use_file, &Agv_BeingIdleNum_Vessel_DelayedNum_WaitingNum, lf);
                    std::thread t2(&AGV_operation_and_its_container::unzip_use_file, &Agv_operation_and_its_container, lf);
                    std::thread t3(&AGV_waitlist_container_count_per_yard_Status::unzip_use_file, &Agv_waitlist_container_count_per_yard_Status, lf);
                    std::thread t4(&AGV_waitlist_QC_Status::unzip_use_file, &Agv_waitlist_QC_Status, lf);
                    std::thread t5(&Berth_Vessel::unzip_use_file, &berth_Vessel, lf);
                    std::thread t6(&YB_Vessel_Num::unzip_use_file, &Yb_Vessel_Num, lf);
                    std::thread t7(&AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum::unzip_file, &Agv_BeingIdleNum_Vessel_DelayedNum_WaitingNum, lf);
                    std::thread t8(&AGV_operation_and_its_container::unzip_file, &Agv_operation_and_its_container, lf);
                    std::thread t9(&AGV_waitlist_container_count_per_yard_Status::unzip_file, &Agv_waitlist_container_count_per_yard_Status, lf);
                    std::thread t10(&AGV_waitlist_QC_Status::unzip_file, &Agv_waitlist_QC_Status, lf);
                    std::thread t11(&Berth_Vessel::unzip_file, &berth_Vessel, lf);
                    std::thread t12(&YB_Vessel_Num::unzip_file, &Yb_Vessel_Num, lf);
                    t1.join();
                    t2.join();
                    t3.join();
                    t4.join();
                    t5.join();
                    t6.join();
                    t7.detach();
                    t8.detach();
                    t9.detach();
                    t10.detach();
                    t11.detach();
                    t12.detach();
                    ClockTime temp;
                    time_t userTimeT = std::mktime(&temp.userTime);
                    time_t newTimeT = userTimeT + (lf - 1) * oneday;
                    Clocktime.update(difftime(newTimeT, Clocktime.current_time_t), 0, 0);
                    putimage(823, 647, &hasten);
                }
            }
        }
    }
}

void visualization::update() {
    BeginBatchDraw();
    if (visualization::stopflag) {
        putimagePNG(770, 848 + 22, &PLAYPNG);
        change_speed.update(1, 0, 0);
        EndBatchDraw();
        return;
    }
    cleardevice();
    putimage(0, 0, &bg);
    putimage(0, 0, &sea);
    putimage(0, 68, &Road);
    putimagePNG(770, 848+22, &HALTPNG);
    putimage(768, 647, &decelerate);
    putimage(823, 647, &hasten);
    for (int i = 0; i < 16; i++) {
        if (i < 12) {
            if (i < 4) {
                berth_Vessel.update(i, 0, 0);
            }
            Agv_operation_and_its_container.update(i, Agv_operation_and_its_container.cp[i].x, Agv_operation_and_its_container.cp[i].y+22);
            Agv_waitlist_container_count_per_yard_Status.update(i, Yblocation.cp[i].x, Yblocation.cp[i].y + 22);
            Agv_waitlist_QC_Status.update(i, Qclocation.cp[i].x, Qclocation.cp[i].y + 23 + 22);
            Yb_Vessel_Num.update(i, Yblocation.cp[i].x, Yblocation.cp[i].y + 22);
            putimagePNG(Qclocation.cp[i].x, Qclocation.cp[i].y + 23 + 22, &Qclocation.QCPNG[i]);
        }
        else {
            Agv_waitlist_container_count_per_yard_Status.update(i, Yblocation.cp[i].x, Yblocation.cp[i].y + 22);
            Yb_Vessel_Num.update(i, Yblocation.cp[i].x, Yblocation.cp[i].y + 22);
        }
    }
    Agv_BeingIdleNum_Vessel_DelayedNum_WaitingNum.update(0, 0, 0);
    change_speed.update(0, 0, 0);
    Clocktime.update(change_speed.tt, 0, 0);
    EndBatchDraw();
}
inline void ConvertToWideChar(const char* src, wchar_t* dest, int destSize) {
    MultiByteToWideChar(CP_ACP, 0, src, -1, dest, destSize);
}
void setFullScreen() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE); 
    RECT desktop;
    GetWindowRect(GetDesktopWindow(), &desktop);
    int screenWidth = desktop.right;
    int screenHeight = desktop.bottom;
    initgraph(screenWidth, screenHeight);
}
int main() {
    char currentDirectory[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, currentDirectory);
    for (int i = 0; i < 3; ++i) {
        PathRemoveFileSpecA(currentDirectory);
    }
    auto loadImage = [&](const char* fileName, IMAGE& img) {
        char fullPath[MAX_PATH];
        PathCombineA(fullPath, currentDirectory, fileName);
        wchar_t fullPathW[MAX_PATH];
        ConvertToWideChar(fullPath, fullPathW, MAX_PATH);
        loadimage(&img, fullPathW);
    };
    loadImage("Image_Materials\\play.png", PLAYPNG);
    loadImage("Image_Materials\\halt.png", HALTPNG);
    loadImage("Image_Materials\\bg.png", bg);
    loadImage("Image_Materials\\sea.png", sea);
    loadImage("Image_Materials\\Road.png", Road);
    loadImage("Image_Materials\\hasten.png", hasten);
    loadImage("Image_Materials\\decelerate.png", decelerate);
    loadImage("Image_Materials\\hasten1.png", hasten1);
    loadImage("Image_Materials\\decelerate1.png", decelerate1);
    cout << "您好，欢迎进入港口可视化初始化界面" << endl;
    cout << "现在的仿真时间是2024/5/3 00:00:00" << endl;
    cout << "请你选择期望的时间计算方式：" << endl;
    cout << "1.过了多少秒后开始仿真" << endl;
    cout << "2.在哪一个时间开始仿真" << endl;
    cout << "请输入1/2：";
    cin >> op;
    if (op == 1) {
        l = Clocktime.calculateTimeFromSeconds();
    }
    else {
        l = Clocktime.readTimeFromInput();
    }
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "请稍等，正在初始化......................................................................................................" << endl;
    Sleep(1000);
    string s;
    lf = l / oneday + 1;
    std::thread t1(&AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum::unzip_use_file, &Agv_BeingIdleNum_Vessel_DelayedNum_WaitingNum, lf);
    std::thread t2(&AGV_operation_and_its_container::unzip_use_file, &Agv_operation_and_its_container, lf);
    std::thread t3(&AGV_waitlist_container_count_per_yard_Status::unzip_use_file, &Agv_waitlist_container_count_per_yard_Status, lf);
    std::thread t4(&AGV_waitlist_QC_Status::unzip_use_file, &Agv_waitlist_QC_Status, lf);
    std::thread t5(&Berth_Vessel::unzip_use_file, &berth_Vessel, lf);
    std::thread t6(&YB_Vessel_Num::unzip_use_file, &Yb_Vessel_Num, lf);
    std::thread t7(&AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum::unzip_file, &Agv_BeingIdleNum_Vessel_DelayedNum_WaitingNum, lf);
    std::thread t8(&AGV_operation_and_its_container::unzip_file, &Agv_operation_and_its_container, lf);
    std::thread t9(&AGV_waitlist_container_count_per_yard_Status::unzip_file, &Agv_waitlist_container_count_per_yard_Status, lf);
    std::thread t10(&AGV_waitlist_QC_Status::unzip_file, &Agv_waitlist_QC_Status, lf);
    std::thread t11(&Berth_Vessel::unzip_file, &berth_Vessel, lf);
    std::thread t12(&YB_Vessel_Num::unzip_file, &Yb_Vessel_Num, lf);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.detach();
    t8.detach();
    t9.detach();
    t10.detach();
    t11.detach();
    t12.detach();
    ld = l % (oneday);
    for (int i = 0; i < ld; i++) {
        for (int j = 0; j < 16; j++) {
            if (j < 12) {
                if (j < 4) {
                    getline(berth_Vessel.file, s);
                }
                getline(Agv_operation_and_its_container.file, s);
                getline(Agv_waitlist_container_count_per_yard_Status.file, s);
                getline(Agv_waitlist_QC_Status.file, s);
                getline(Yb_Vessel_Num.file, s);
            }
            else {
                getline(Yb_Vessel_Num.file, s);
                getline(Agv_waitlist_container_count_per_yard_Status.file, s);
            }
        }
        getline(Agv_BeingIdleNum_Vessel_DelayedNum_WaitingNum.file, s);
        cout << ".";
    }
    cout << endl;
    cout << "请输入你期望的界面帧数(如果要加速请输入0):";
    cin >> change_speed.zhenshu;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "请稍等，正在初始化......................................................................................................" << endl;
    cout << endl;
    Sleep(1000);
    cout << "请输入你期望几秒取一次数据(必须是正整数):";
    cin >> change_speed.tt;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "请稍等，正在初始化......................................................................................................" << endl;
    cout << endl;
    Sleep(1000);
    cout << "......................................................................................................................." << endl;
    cout << "开始运行!" << endl;
    Clocktime.current_time_t = mktime(&Clocktime.userTime);
    setFullScreen();
    setbkcolor(WHITE);
    for (int i = l; i <= 6048000; i++) {
        visualization::stop();
        while (visualization::stopflag) {
            visualization::update();
            visualization::stop();
        }
        for (int k = 0; k < change_speed.tt-1; k++) {
            for (int j = 0; j < 16; j++) {
                if (j < 12) {
                    if (j < 4) {
                        getline(berth_Vessel.file, s);
                    }
                    getline(Agv_operation_and_its_container.file, s);
                    getline(Agv_waitlist_container_count_per_yard_Status.file, s);
                    getline(Agv_waitlist_QC_Status.file, s);
                    getline(Yb_Vessel_Num.file, s);
                }
                else {
                    getline(Yb_Vessel_Num.file, s);
                    getline(Agv_waitlist_container_count_per_yard_Status.file, s);
                }
            }
            getline(Agv_BeingIdleNum_Vessel_DelayedNum_WaitingNum.file, s);
            ld++;
            if (ld == (oneday)) {
                ld = 0;
                lf += 1;
                std::thread t1(&AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum::use_file, &Agv_BeingIdleNum_Vessel_DelayedNum_WaitingNum, lf);
                std::thread t2(&AGV_operation_and_its_container::use_file, &Agv_operation_and_its_container, lf);
                std::thread t3(&AGV_waitlist_container_count_per_yard_Status::use_file, &Agv_waitlist_container_count_per_yard_Status, lf);
                std::thread t4(&AGV_waitlist_QC_Status::use_file, &Agv_waitlist_QC_Status, lf);
                std::thread t5(&Berth_Vessel::use_file, &berth_Vessel, lf);
                std::thread t6(&YB_Vessel_Num::use_file, &Yb_Vessel_Num, lf);
                std::thread t7(&AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum::unzip_file, &Agv_BeingIdleNum_Vessel_DelayedNum_WaitingNum, lf);
                std::thread t8(&AGV_operation_and_its_container::unzip_file, &Agv_operation_and_its_container, lf);
                std::thread t9(&AGV_waitlist_container_count_per_yard_Status::unzip_file, &Agv_waitlist_container_count_per_yard_Status, lf);
                std::thread t10(&AGV_waitlist_QC_Status::unzip_file, &Agv_waitlist_QC_Status, lf);
                std::thread t11(&Berth_Vessel::unzip_file, &berth_Vessel, lf);
                std::thread t12(&YB_Vessel_Num::unzip_file, &Yb_Vessel_Num, lf);
                t1.join();
                t2.join();
                t3.join();
                t4.join();
                t5.join();
                t6.join();
                t7.detach();
                t8.detach();
                t9.detach();
                t10.detach();
                t11.detach();
                t12.detach();
            }
        }
        visualization::update();
        ld++;
        if (ld == (oneday)) {
            ld = 0;
            lf += 1;
            std::thread t1(&AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum::use_file, &Agv_BeingIdleNum_Vessel_DelayedNum_WaitingNum, lf);
            std::thread t2(&AGV_operation_and_its_container::use_file, &Agv_operation_and_its_container, lf);
            std::thread t3(&AGV_waitlist_container_count_per_yard_Status::use_file, &Agv_waitlist_container_count_per_yard_Status, lf);
            std::thread t4(&AGV_waitlist_QC_Status::use_file, &Agv_waitlist_QC_Status, lf);
            std::thread t5(&Berth_Vessel::use_file, &berth_Vessel, lf);
            std::thread t6(&YB_Vessel_Num::use_file, &Yb_Vessel_Num, lf);
            std::thread t7(&AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum::unzip_file, &Agv_BeingIdleNum_Vessel_DelayedNum_WaitingNum, lf);
            std::thread t8(&AGV_operation_and_its_container::unzip_file, &Agv_operation_and_its_container, lf);
            std::thread t9(&AGV_waitlist_container_count_per_yard_Status::unzip_file, &Agv_waitlist_container_count_per_yard_Status, lf);
            std::thread t10(&AGV_waitlist_QC_Status::unzip_file, &Agv_waitlist_QC_Status, lf);
            std::thread t11(&Berth_Vessel::unzip_file, &berth_Vessel, lf);
            std::thread t12(&YB_Vessel_Num::unzip_file, &Yb_Vessel_Num, lf);
            t1.join();
            t2.join();
            t3.join();
            t4.join();
            t5.join();
            t6.join();
            t7.detach();
            t8.detach();
            t9.detach();
            t10.detach();
            t11.detach();
            t12.detach();
        }
        for (int i = 1; i <= change_speed.zhenshu*50000; i++) {
            visualization::stop();
            if (visualization::stopflag)break;
        }
    }
    closegraph();
    return 0;
}
