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
#include "tools.h"    
#include "vector2.h"  
#include "AGV_operation_and_its_container.h"
#include "QCLocation.h"
#include "AGV_waitlist_container_count_per_yard.h"
#include "AGV_waitlist_QC.h"
#include "YBLocation.h"
#include "YB_Vessel_Num.h"
#include "ClockTime.h"
#include "AGV_BeingIdle.h"
#include "Berth_Vessel.h"
#pragma comment(lib, "winmm.lib")  
using namespace std;
AGV_operation_and_its_container Agv_operation_and_its_container;
QCLocation Qclocation;
AGV_waitlist_container_count_per_yard Agv_waitlist_container_count_per_yard;
AGV_waitlist_QC Agv_waitlist_QC;
YBLocation Yblocation;
ClockTime Clocktime;
YB_Vessel_Num Yb_Vessel_Num;
AGV_BeingIdle Agv_BeingIdle;
Berth_Vessel berth_Vessel;
IMAGE bg;
IMAGE PLAYPNG;
IMAGE HALTPNG;
int tt;
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
            if (msg.x >= 760 && msg.x <= 860 && msg.y >= 848 && msg.y <= 952) {
                if (stopflag == false)stopflag = true;
                else stopflag = false;
            }
        }
    }
}
void visualization::update() {
    BeginBatchDraw();
    cleardevice();
    putimage(0, 0, &bg);
    if(visualization::stopflag==true)putimagePNG(760, 848, &PLAYPNG);
    else putimagePNG(760, 848, &HALTPNG);
    for (int i = 0; i < 16; i++) {
        if (i < 12) {
            if (i < 4) {
                berth_Vessel.update(i, 0, 0);
            }
            Agv_operation_and_its_container.update(i, Agv_operation_and_its_container.cp[i].x, Agv_operation_and_its_container.cp[i].y);
            Agv_waitlist_container_count_per_yard.update(i, Yblocation.cp[i].x, Yblocation.cp[i].y);
            Agv_waitlist_QC.update(i, Qclocation.cp[i].x, Qclocation.cp[i].y+23);
            Yb_Vessel_Num.update(i, Yblocation.cp[i].x, Yblocation.cp[i].y);
            putimagePNG(Qclocation.cp[i].x, Qclocation.cp[i].y+23, &Qclocation.QCPNG[i]);
        }
        else {
            Agv_waitlist_container_count_per_yard.update(i, Yblocation.cp[i].x, Yblocation.cp[i].y);
            Yb_Vessel_Num.update(i, Yblocation.cp[i].x, Yblocation.cp[i].y);
        }
    }
    Agv_BeingIdle.update(0, 0, 0);
    Clocktime.update(tt, 0, 0);
    EndBatchDraw();
}
inline void ConvertToWideChar(const char* src, wchar_t* dest, int destSize) {
    MultiByteToWideChar(CP_ACP, 0, src, -1, dest, destSize);
}
int main() {
    char currentDirectory[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, currentDirectory);
    for (int i = 0; i < 3; ++i) {
        PathRemoveFileSpecA(currentDirectory);
    }
    const char* fileName1 = "Image_Materials\\play.png";
    char fullPath1[MAX_PATH];
    PathCombineA(fullPath1, currentDirectory, fileName1);
    wchar_t fullPathW1[MAX_PATH];
    ConvertToWideChar(fullPath1, fullPathW1, MAX_PATH);
    const char* fileName2 = "Image_Materials\\halt.png";
    char fullPath2[MAX_PATH];
    PathCombineA(fullPath2, currentDirectory, fileName2);
    wchar_t fullPathW2[MAX_PATH];
    ConvertToWideChar(fullPath2, fullPathW2, MAX_PATH);
    const char* fileName3 = "Image_Materials\\bg.png";
    char fullPath3[MAX_PATH];
    PathCombineA(fullPath3, currentDirectory, fileName3);
    wchar_t fullPathW3[MAX_PATH];
    ConvertToWideChar(fullPath3, fullPathW3, MAX_PATH);
    loadimage(&PLAYPNG, fullPathW1);
    loadimage(&HALTPNG, fullPathW2);
    loadimage(&bg, fullPathW3);
    long long op,l,zhenshu;
    cout << "您好，欢迎进入港口可视化初始化界面" << endl;
    cout<<"现在的仿真时间是2024/5/3 00:00:00" << endl;
    cout << "请你选择期望的时间计算方式：" << endl;
    cout << "1.过了多少秒后开始仿真" << endl;
    cout << "2.在哪一个时间开始仿真" << endl;
    cout << "请输入1/2：";
    cin >> op;
    if (op == 1) {
        l=Clocktime.calculateTimeFromSeconds();
    }
    else {
        l=Clocktime.readTimeFromInput();
    }
    cout << "------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout << "请稍等，正在初始化......................................................................................................" << endl;
    Sleep(1000);
    string s;
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < 16; j++) {
            if (j < 12) {
                if (j < 4) {
                    getline(berth_Vessel.file, s);
                }
                getline(Agv_operation_and_its_container.file,s);
                getline(Agv_waitlist_container_count_per_yard.file,s);
                getline(Agv_waitlist_QC.file, s);
                getline(Yb_Vessel_Num.file, s);
            }
            else {
                getline(Yb_Vessel_Num.file, s);
                getline(Agv_waitlist_container_count_per_yard.file, s);
            }
        }
        getline(Agv_BeingIdle.file, s);
        cout << ".";
    }
    cout << endl;
    cout << "请输入你期望的界面帧数(如果要加速请输入0):";
    cin >> zhenshu;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "请稍等，正在初始化......................................................................................................" << endl;
    cout << endl;
    Sleep(1000);
    cout << "请输入你期望几秒取一次数据(必须是正整数):";
    cin >> tt;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "请稍等，正在初始化......................................................................................................" << endl;
    cout << endl;
    Sleep(1000);
    cout << "......................................................................................................................." << endl;
    cout << "开始运行!" << endl;
    Clocktime.current_time_t = mktime(&Clocktime.userTime);
    initgraph(2560, 1600);
    setbkcolor(WHITE);   
    for (int i = l/tt; i <= 6048000/tt; i++) {
        visualization::stop();
        visualization::update();
        while (visualization::stopflag) {
            visualization::stop();
        }
        Sleep(zhenshu);
        for (int k = 0; k < tt; k++) {
            for (int j = 0; j < 16; j++) {
                if (j < 12) {
                    if (j < 4) {
                        getline(berth_Vessel.file, s);
                    }
                    getline(Agv_operation_and_its_container.file, s);
                    getline(Agv_waitlist_container_count_per_yard.file, s);
                    getline(Agv_waitlist_QC.file, s);
                    getline(Yb_Vessel_Num.file, s);
                }
                else {
                    getline(Yb_Vessel_Num.file, s);
                    getline(Agv_waitlist_container_count_per_yard.file, s);
                }
            }
            getline(Agv_BeingIdle.file, s);
        }
    }
    closegraph(); 
    return 0;
}
