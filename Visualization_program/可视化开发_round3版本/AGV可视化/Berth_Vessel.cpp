#include "Berth_Vessel.h"
#include "tools.h"    
#include "vector2.h"  
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
inline void unzipUsingPowerShell(const string& zipPath, const string& extractPath) {
    string command = "powershell -Command \"Expand-Archive -Path '" + zipPath + "' -DestinationPath '" + extractPath + "' -Force\"";
    system(command.c_str());
}
Berth_Vessel::Berth_Vessel() {
    const char* fileName1 = "Image_Materials\\vessel.png";
    char fullPath1[MAX_PATH];
    PathCombineA(fullPath1, currentDirectory, fileName1);
    wchar_t fullPathW[MAX_PATH];
    ConvertToWideChar(fullPath1, fullPathW, MAX_PATH);
    loadimage(&vessel, fullPathW);

    const char* fileName2 = "Image_Materials\\berth.png";
    char fullPath2[MAX_PATH];
    PathCombineA(fullPath2, currentDirectory, fileName2);
    wchar_t fullPathW2[MAX_PATH];
    ConvertToWideChar(fullPath2, fullPathW2, MAX_PATH);
    loadimage(&berth, fullPathW2);
}
void Berth_Vessel::update(int i, double x, double y) {
    string s, s1;
    wstring s_w;
    getline(file, s);
    stringstream ss(s);
    getline(ss, s1, ',');

    getline(ss, s1, ',');
    putimagePNG(i * 400 + 28, 0, &berth);
    if(!s1.empty()){
        putimagePNG(i * 400 + 30, 0, &vessel);
    }
    s_w = wstring(s1.begin(), s1.end());
    settextcolor(BLACK);
    settextstyle(15, 0, L"Consolas");
    outtextxy(i * 400 + 290 + 30, 14, s_w.c_str());

    getline(ss, s1, ',');
    s_w = wstring(s1.begin(), s1.end());
    settextcolor(BLACK);
    settextstyle(15, 0, L"Consolas");
    outtextxy(i * 400 + 2 + 30, 14, s_w.c_str());

    if (!s1.empty()) {
        for (int j = 0; j < 30; j++) {
            getline(ss, s1, ',');
            s_w = wstring(s1.begin(), s1.end());
            settextcolor(BLACK);
            settextstyle(12, 0, L"Consolas");
            outtextxy((i * 400) + 90 + (j % 10 * 20) + 30, 13 * (j / 10) + 3, s_w.c_str());
        }
    }
}
void Berth_Vessel::setfile(int x) {
    /*if (file.is_open())file.close();
    string ch = to_string(x);
    string fileName = "Calculated_Data\\Berth_Vessel" + std::to_string(x) + ".txt";
    const char* fileName1 = fileName.c_str();
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName1);
    file.open(fullPath);*/
    if (file.is_open()) {
        file.close();
    }
    for (int i = 1; i <= 70; i++) {
        string lastfileName = "Calculated_Data\\Berth_Vessel" + std::to_string(i) + ".txt";
        const char* lastfileName1 = lastfileName.c_str();
        char lastfullPath[MAX_PATH];
        PathCombineA(lastfullPath, currentDirectory, lastfileName1);
        remove(lastfullPath);
    }
    string zipFileName = "Calculated_Data\\Berth_Vessel" + to_string(x) + ".zip";
    char zipFullPath[MAX_PATH];
    PathCombineA(zipFullPath, currentDirectory, zipFileName.c_str());
    string zipFilePath = zipFullPath;
    char tempFullPath[MAX_PATH];
    PathCombineA(tempFullPath, currentDirectory, "Calculated_Data");
    string tempPath = tempFullPath;
    unzipUsingPowerShell(zipFilePath, tempFullPath);
    string fileName = "Calculated_Data\\Berth_Vessel" + std::to_string(x) + ".txt";
    const char* fileName1 = fileName.c_str();
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName1);
    file.open(fullPath);
}
Berth_Vessel::~Berth_Vessel() {
    file.close();
}