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
void AGV_BeingIdleNum_Vessel_DelayedNum::setfile(int x) {
    if (file.is_open())file.close();
    string ch = to_string(x);
    string fileName = "Calculated_Data\\AGV_BeingIdleNum_Vessel_DelayedNum" + std::to_string(x) + ".txt";
    const char* fileName1 = fileName.c_str();
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName1);
    file.open(fullPath);
}
AGV_BeingIdleNum_Vessel_DelayedNum::~AGV_BeingIdleNum_Vessel_DelayedNum() {
    file.close();
}