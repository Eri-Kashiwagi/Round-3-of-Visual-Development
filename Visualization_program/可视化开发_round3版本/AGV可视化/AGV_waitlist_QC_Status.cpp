#include "AGV_waitlist_QC_Status.h"
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <string>
#include <sstream> 
#include <windows.h>
#include <shlwapi.h>
#include<unordered_map>
using namespace std;
inline void ConvertToWideChar(const char* src, wchar_t* dest, int destSize) {
    MultiByteToWideChar(CP_ACP, 0, src, -1, dest, destSize);
}
AGV_waitlist_QC_Status::AGV_waitlist_QC_Status() {
    mp = {
        {0, "QC"},
        {1, "SettingUp"},
        {2, "RestoringtoDischarge"},
        {3, "Discharging"},
        {4, "HoldingonDischarging"},
        {5, "RestoringtoLoad"},
        {6, "Loading"},
        {7, "HoldingonLoading"}
    };
    imagemp = {
        {"QC", 0},
        {"SettingUp", 1},
        {"RestoringtoDischarge", 2},
        {"Discharging", 3},
        {"HoldingonDischarging", 4},
        {"RestoringtoLoad", 5},
        {"Loading", 6},
        {"HoldingonLoading", 7}
    };
    for (int i = 0; i < 8; i++) {
        string fileName = "Image_Materials\\QC_" + mp[i] + ".png";
        const char* fileName1 = fileName.c_str();
        char fullPath1[MAX_PATH];
        PathCombineA(fullPath1, currentDirectory, fileName1);
        wchar_t fullPathW[MAX_PATH];
        ConvertToWideChar(fullPath1, fullPathW, MAX_PATH);
        loadimage(&status[i], fullPathW);
    }
}
void AGV_waitlist_QC_Status::update(int i, double x, double y) {
    string s, s1;
    wstring s_w;
    getline(file, s);
    stringstream ss(s);
    getline(ss, s1, ',');
    getline(ss, s1, ',');
    putimage(x, y, &status[imagemp[s1]]);
    int d = 1;
    while (getline(ss, s1, ',')) {
        if (d % 2 != 0) {
            s_w = wstring(s1.begin(), s1.end());
            settextstyle(15, 0, L"Tahoma");
            outtextxy(x + 50, y + (d - 1) / 2 * 20, s_w.c_str());
        }
        else {
            s_w = wstring(s1.begin(), s1.end());
            settextstyle(15, 0, L"Tahoma");
            outtextxy(x + 50 + 40, y + (d - 1) / 2 * 20, s_w.c_str());
        }
        d++;
    }
}
void AGV_waitlist_QC_Status::setfile(int x) {
    if (file.is_open())file.close();
    string ch = to_string(x);
    string fileName = "Calculated_Data\\AGV_waitlist_QC_Status" + std::to_string(x) + ".txt";
    const char* fileName1 = fileName.c_str();
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName1);
    file.open(fullPath);
}
AGV_waitlist_QC_Status::~AGV_waitlist_QC_Status() {
    file.close();
}