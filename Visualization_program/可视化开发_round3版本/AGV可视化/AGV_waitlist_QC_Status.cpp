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
inline void unzip_fileUsingPowerShell(const string& zipPath, const string& extractPath) {
    string command = "powershell -Command \"Expand-Archive -Path '" + zipPath + "' -DestinationPath '" + extractPath + "' -Force\"";
    system(command.c_str());
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
    const char* fileName2 = "Image_Materials\\QuaySide.png";
    char fullPath2[MAX_PATH];
    PathCombineA(fullPath2, currentDirectory, fileName2);
    wchar_t fullPathW2[MAX_PATH];
    ConvertToWideChar(fullPath2, fullPathW2, MAX_PATH);
    loadimage(&quayside, fullPathW2);
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
    putimage(x + 50+1, y, &quayside);
    while (getline(ss, s1, ',')) {
        if (d % 2 != 0) {
            s_w = wstring(s1.begin(), s1.end());
            settextstyle(15, 0, L"Tahoma");
            outtextxy(x + 50+3, y + (d - 1) / 2 * 20+1, s_w.c_str());
        }
        else {
            s_w = wstring(s1.begin(), s1.end());
            settextstyle(15, 0, L"Tahoma");
            outtextxy(x + 50 + 40+3, y + (d - 1) / 2 * 20+1, s_w.c_str());
        }
        d++;
    }
}
void AGV_waitlist_QC_Status::unzip_use_file(int x) {
    if (file.is_open()) {
        file.close();
    }
    for (int i = 1; i <= 70; i++) {
        string lastfileName = "Calculated_Data\\AGV_waitlist_QC_Status" + std::to_string(i) + ".txt";
        const char* lastfileName1 = lastfileName.c_str();
        char lastfullPath[MAX_PATH];
        PathCombineA(lastfullPath, currentDirectory, lastfileName1);
        remove(lastfullPath);
    }
    string zipFileName = "Calculated_Data\\AGV_waitlist_QC_Status" + to_string(x) + ".zip";
    char zipFullPath[MAX_PATH];
    PathCombineA(zipFullPath, currentDirectory, zipFileName.c_str());
    string zipFilePath = zipFullPath;
    char tempFullPath[MAX_PATH];
    PathCombineA(tempFullPath, currentDirectory, "Calculated_Data");
    string tempPath = tempFullPath;
    unzip_fileUsingPowerShell(zipFilePath, tempFullPath);
    string fileName = "Calculated_Data\\AGV_waitlist_QC_Status" + std::to_string(x) + ".txt";
    const char* fileName1 = fileName.c_str();
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName1);
    file.open(fullPath);
}
void AGV_waitlist_QC_Status::unzip_file(int x) {
    x += 1;
    if (x > 71 || x < 1)return;
    string zipFileName = "Calculated_Data\\AGV_waitlist_QC_Status" + to_string(x) + ".zip";
    char zipFullPath[MAX_PATH];
    PathCombineA(zipFullPath, currentDirectory, zipFileName.c_str());
    string zipFilePath = zipFullPath;
    char tempFullPath[MAX_PATH];
    PathCombineA(tempFullPath, currentDirectory, "Calculated_Data");
    string tempPath = tempFullPath;
    unzip_fileUsingPowerShell(zipFilePath, tempFullPath);
}
void AGV_waitlist_QC_Status::use_file(int x) {
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