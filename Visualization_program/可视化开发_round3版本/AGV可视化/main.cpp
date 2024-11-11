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
                    Agv_BeingIdleNum_Vessel_DelayedNum_WaitingNum.setfile(lf);
                    Agv_operation_and_its_container.setfile(lf);
                    Agv_waitlist_container_count_per_yard_Status.setfile(lf);
                    Agv_waitlist_QC_Status.setfile(lf);
                    berth_Vessel.setfile(lf);
                    Yb_Vessel_Num.setfile(lf);
                    ClockTime temp;
                    time_t userTimeT = std::mktime(&temp.userTime);
                    time_t newTimeT = userTimeT + (lf-1)* oneday;
                    Clocktime.update(difftime(newTimeT,Clocktime.current_time_t),0,0);
                    Sleep(100);
                    putimage(768, 647, &decelerate);
                }
                else if (msg.x >= 823 && msg.x <= 873 && msg.y >= 647 && msg.y <= 717) {
                    putimage(823, 647, &hasten1);
                    ld = 0;
                    lf++;
                    Agv_BeingIdleNum_Vessel_DelayedNum_WaitingNum.setfile(lf);
                    Agv_operation_and_its_container.setfile(lf);
                    Agv_waitlist_container_count_per_yard_Status.setfile(lf);
                    Agv_waitlist_QC_Status.setfile(lf);
                    berth_Vessel.setfile(lf);
                    Yb_Vessel_Num.setfile(lf);
                    ClockTime temp;
                    time_t userTimeT = std::mktime(&temp.userTime);
                    time_t newTimeT = userTimeT + (lf - 1) * oneday;
                    Clocktime.update(difftime(newTimeT, Clocktime.current_time_t), 0, 0);
                    Sleep(100);
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
    const char* fileName4 = "Image_Materials\\sea.png";
    char fullPath4[MAX_PATH];
    PathCombineA(fullPath4, currentDirectory, fileName4);
    wchar_t fullPathW4[MAX_PATH];
    ConvertToWideChar(fullPath4, fullPathW4, MAX_PATH);
    const char* fileName5 = "Image_Materials\\Road.png";
    char fullPath5[MAX_PATH];
    PathCombineA(fullPath5, currentDirectory, fileName5);
    wchar_t fullPathW5[MAX_PATH];
    ConvertToWideChar(fullPath5, fullPathW5, MAX_PATH);
    const char* fileName6 = "Image_Materials\\hasten.png";
    char fullPath6[MAX_PATH];
    PathCombineA(fullPath6, currentDirectory, fileName6);
    wchar_t fullPathW6[MAX_PATH];
    ConvertToWideChar(fullPath6, fullPathW6, MAX_PATH);
    const char* fileName7 = "Image_Materials\\decelerate.png";
    char fullPath7[MAX_PATH];
    PathCombineA(fullPath7, currentDirectory, fileName7);
    wchar_t fullPathW7[MAX_PATH];
    ConvertToWideChar(fullPath7, fullPathW7, MAX_PATH);
    const char* fileName8 = "Image_Materials\\hasten1.png";
    char fullPath8[MAX_PATH];
    PathCombineA(fullPath8, currentDirectory, fileName8);
    wchar_t fullPathW8[MAX_PATH];
    ConvertToWideChar(fullPath8, fullPathW8, MAX_PATH);
    const char* fileName9 = "Image_Materials\\decelerate1.png";
    char fullPath9[MAX_PATH];
    PathCombineA(fullPath9, currentDirectory, fileName9);
    wchar_t fullPathW9[MAX_PATH];
    ConvertToWideChar(fullPath9, fullPathW9, MAX_PATH);
    loadimage(&PLAYPNG, fullPathW1);
    loadimage(&HALTPNG, fullPathW2);
    loadimage(&bg, fullPathW3);
    loadimage(&sea, fullPathW4);
    loadimage(&Road, fullPathW5);
    loadimage(&hasten, fullPathW6);
    loadimage(&decelerate, fullPathW7);
    loadimage(&hasten1, fullPathW8);
    loadimage(&decelerate1, fullPathW9);
    cout << "���ã���ӭ����ۿڿ��ӻ���ʼ������" << endl;
    cout << "���ڵķ���ʱ����2024/5/3 00:00:00" << endl;
    cout << "����ѡ��������ʱ����㷽ʽ��" << endl;
    cout << "1.���˶������ʼ����" << endl;
    cout << "2.����һ��ʱ�俪ʼ����" << endl;
    cout << "������1/2��";
    cin >> op;
    if (op == 1) {
        l = Clocktime.calculateTimeFromSeconds();
    }
    else {
        l = Clocktime.readTimeFromInput();
    }
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "���Եȣ����ڳ�ʼ��......................................................................................................" << endl;
    Sleep(1000);
    string s;
    lf = l / oneday + 1;
    Agv_BeingIdleNum_Vessel_DelayedNum_WaitingNum.setfile(lf);
    Agv_operation_and_its_container.setfile(lf);
    Agv_waitlist_container_count_per_yard_Status.setfile(lf);
    Agv_waitlist_QC_Status.setfile(lf);
    berth_Vessel.setfile(lf);
    Yb_Vessel_Num.setfile(lf);
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
    cout << "�������������Ľ���֡��(���Ҫ����������0):";
    cin >> change_speed.zhenshu;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "���Եȣ����ڳ�ʼ��......................................................................................................" << endl;
    cout << endl;
    Sleep(1000);
    cout << "����������������ȡһ������(������������):";
    cin >> change_speed.tt;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "���Եȣ����ڳ�ʼ��......................................................................................................" << endl;
    cout << endl;
    Sleep(1000);
    cout << "......................................................................................................................." << endl;
    cout << "��ʼ����!" << endl;
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
                Agv_BeingIdleNum_Vessel_DelayedNum_WaitingNum.setfile(lf);
                Agv_operation_and_its_container.setfile(lf);
                Agv_waitlist_container_count_per_yard_Status.setfile(lf);
                Agv_waitlist_QC_Status.setfile(lf);
                berth_Vessel.setfile(lf);
                Yb_Vessel_Num.setfile(lf);
            }
        }
        visualization::update();
        ld++;
        if (ld == (oneday)) {
            ld = 0;
            lf += 1;
            Agv_BeingIdleNum_Vessel_DelayedNum_WaitingNum.setfile(lf);
            Agv_operation_and_its_container.setfile(lf);
            Agv_waitlist_container_count_per_yard_Status.setfile(lf);
            Agv_waitlist_QC_Status.setfile(lf);
            berth_Vessel.setfile(lf);
            Yb_Vessel_Num.setfile(lf);
        }
        for (int i = 1; i <= change_speed.zhenshu*50000; i++) {
            visualization::stop();
            if (visualization::stopflag)break;
        }
    }
    closegraph();
    return 0;
}
