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
        outtextxy(x - 25 + 26 * (j % 5), y + 150 + 160 + (j) / 5 * 20, s_w.c_str());
    }
}
void YB_Vessel_Num::setfile(int x) {
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