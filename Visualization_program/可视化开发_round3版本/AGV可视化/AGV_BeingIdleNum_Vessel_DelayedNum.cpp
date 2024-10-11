#include "AGV_BeingIdleNum_Vessel_DelayedNum.h"
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <string>
#include <sstream> 
#include <windows.h>
#include <shlwapi.h>
using namespace std;
#pragma comment(lib, "Shlwapi.lib")
AGV_BeingIdleNum_Vessel_DelayedNum::AGV_BeingIdleNum_Vessel_DelayedNum() {
    char currentDirectory[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, currentDirectory); 
    for (int i = 0; i < 3; ++i) {
        PathRemoveFileSpecA(currentDirectory);  
    }
    const char* fileName = "Calculated_Data\\AGV_BeingIdleNum_Vessel_DelayedNum.txt";
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName); 
    file.open(fullPath);
}
void AGV_BeingIdleNum_Vessel_DelayedNum::update(int i, double x, double y) {
    string s, s1;
    getline(file, s);
    stringstream ss(s);
    getline(ss, s1, ',');
    getline(ss, s1, ',');
    s1 = "AGV_BeingIdleNum: " + s1;
    wstring s_w = wstring(s1.begin(), s1.end());
    settextcolor(BLACK);
    settextstyle(50, 0, L"Consolas");
    outtextxy(50, 950, s_w.c_str());

    getline(ss, s1, ',');
    s1 = "Vessel_Delayed: " + s1;
    s_w = wstring(s1.begin(), s1.end());
    settextcolor(BLACK);
    settextstyle(50, 0, L"Consolas");
    outtextxy(1200, 950, s_w.c_str());
}
AGV_BeingIdleNum_Vessel_DelayedNum::~AGV_BeingIdleNum_Vessel_DelayedNum() {
    file.close();
}