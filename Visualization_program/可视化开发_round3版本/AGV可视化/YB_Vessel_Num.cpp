#include "YB_Vessel_Num.h"
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <string>
#include <sstream> 
#include <windows.h>
#include <shlwapi.h>
using namespace std;
inline void ConvertToWideChar(const char* src, wchar_t* dest, int destSize) {
    MultiByteToWideChar(CP_ACP, 0, src, -1, dest, destSize);
}
inline void unzip_fileUsingPowerShell(const string& zipPath, const string& extractPath) {
    string command = "powershell -Command \"Expand-Archive -Path '" + zipPath + "' -DestinationPath '" + extractPath + "' -Force\"";
    system(command.c_str());
}
YB_Vessel_Num::YB_Vessel_Num() {
    string fileName = "Image_Materials\\YardBlock.png";
    const char* fileName1 = fileName.c_str();
    char fullPath1[MAX_PATH];
    PathCombineA(fullPath1, currentDirectory, fileName1);
    wchar_t fullPathW[MAX_PATH];
    ConvertToWideChar(fullPath1, fullPathW, MAX_PATH);
    loadimage(&YardBlock, fullPathW);
}
void YB_Vessel_Num::update(int i, double x, double y) {
    string s, s1;
    wstring s_w;
    getline(file, s);
    stringstream ss(s);
    getline(ss, s1, ',');
    putimage(x - 25 -10 , y + 150 + 160-10, &YardBlock);
    for (int j = 0; j <= 29; j++) {
        getline(ss, s1, ',');
        s_w = wstring(s1.begin(), s1.end());
        settextstyle(13, 0, L"Tahoma");
        outtextxy(x - 25 + 26 * (j % 5)-5, y + 150 + 160 + (j) / 5 * 20, s_w.c_str());
    }
}
void YB_Vessel_Num::unzip_use_file(int x) {
    if (file.is_open()) {
        file.close();
    }
    for (int i = 1; i <= 70; i++) {
        string lastfileName = "Calculated_Data\\YB_Vessel_Num" + std::to_string(i) + ".txt";
        const char* lastfileName1 = lastfileName.c_str();
        char lastfullPath[MAX_PATH];
        PathCombineA(lastfullPath, currentDirectory, lastfileName1);
        remove(lastfullPath);
    }
    string zipFileName = "Calculated_Data\\YB_Vessel_Num" + to_string(x) + ".zip";
    char zipFullPath[MAX_PATH];
    PathCombineA(zipFullPath, currentDirectory, zipFileName.c_str());
    string zipFilePath = zipFullPath;
    char tempFullPath[MAX_PATH];
    PathCombineA(tempFullPath, currentDirectory, "Calculated_Data");
    string tempPath = tempFullPath;
    unzip_fileUsingPowerShell(zipFilePath, tempFullPath);
    string fileName = "Calculated_Data\\YB_Vessel_Num" + std::to_string(x) + ".txt";
    const char* fileName1 = fileName.c_str();
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName1);
    file.open(fullPath);
}
void YB_Vessel_Num::unzip_file(int x) {
    x += 1;
    if (x > 71 || x < 1)return;
    string zipFileName = "Calculated_Data\\YB_Vessel_Num" + to_string(x) + ".zip";
    char zipFullPath[MAX_PATH];
    PathCombineA(zipFullPath, currentDirectory, zipFileName.c_str());
    string zipFilePath = zipFullPath;
    char tempFullPath[MAX_PATH];
    PathCombineA(tempFullPath, currentDirectory, "Calculated_Data");
    string tempPath = tempFullPath;
    unzip_fileUsingPowerShell(zipFilePath, tempFullPath);
}
void YB_Vessel_Num::use_file(int x) {
    if (file.is_open())file.close();
    string ch = to_string(x);
    string fileName = "Calculated_Data\\YB_Vessel_Num" + std::to_string(x) + ".txt";
    const char* fileName1 = fileName.c_str();
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName1);
    file.open(fullPath);
}
YB_Vessel_Num::~YB_Vessel_Num() {
    file.close();
}