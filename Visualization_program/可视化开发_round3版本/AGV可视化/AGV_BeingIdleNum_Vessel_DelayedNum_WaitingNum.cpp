#include "AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum.h"
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <string>
#include <sstream> 
#include <windows.h>
#include <shlwapi.h>
using namespace std;
#pragma comment(lib, "Shlwapi.lib")
inline void unzipUsingPowerShell(const string& zipPath, const string& extractPath) {
    string command = "powershell -Command \"Expand-Archive -Path '" + zipPath + "' -DestinationPath '" + extractPath + "' -Force\"";
    system(command.c_str());
}
AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum::AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum() {
}
void AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum::update(int i, double x, double y) {
    string s, s1;
    getline(file, s);
    stringstream ss(s);
    getline(ss, s1, ',');
    getline(ss, s1, ',');
    s1 = "AGV_BeingIdleNum: " + s1;
    wstring s_w = wstring(s1.begin(), s1.end());
    settextcolor(BLACK);
    settextstyle(40, 0, L"Consolas");
    outtextxy(50, 940+12, s_w.c_str());

    getline(ss, s1, ',');
    s1 = "Vessel_Delayed: " + s1;
    s_w = wstring(s1.begin(), s1.end());
    settextcolor(BLACK);
    settextstyle(40, 0, L"Consolas");
    outtextxy(1250, 940+12, s_w.c_str());

    getline(ss, s1, ',');
    s1 = "Vessel_Waiting: " + s1;
    s_w = wstring(s1.begin(), s1.end());
    settextcolor(BLACK);
    settextstyle(40, 0, L"Consolas");
    outtextxy(1250, 980+12, s_w.c_str());
}
void AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum::setfile(int x) {
    /*if (file.is_open())file.close();
    string ch = to_string(x);
    string fileName = "Calculated_Data\\AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum" + std::to_string(x) + ".txt";
    const char* fileName1 = fileName.c_str();
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName1);
    file.open(fullPath);*/
    if (file.is_open()) {
        file.close();
    }
    for (int i = 1; i <= 70; i++) {
        string lastfileName = "Calculated_Data\\AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum" + std::to_string(i) + ".txt";
        const char* lastfileName1 = lastfileName.c_str();
        char lastfullPath[MAX_PATH];
        PathCombineA(lastfullPath, currentDirectory, lastfileName1);
        remove(lastfullPath);
    }
    string zipFileName = "Calculated_Data\\AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum" + to_string(x) + ".zip";
    char zipFullPath[MAX_PATH];
    PathCombineA(zipFullPath, currentDirectory, zipFileName.c_str());
    string zipFilePath = zipFullPath;
    char tempFullPath[MAX_PATH];
    PathCombineA(tempFullPath, currentDirectory, "Calculated_Data");
    string tempPath = tempFullPath;
    unzipUsingPowerShell(zipFilePath, tempFullPath);
    string fileName = "Calculated_Data\\AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum" + std::to_string(x) + ".txt";
    const char* fileName1 = fileName.c_str();
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName1);
    file.open(fullPath);
}
AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum::~AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum() {
    file.close();
}