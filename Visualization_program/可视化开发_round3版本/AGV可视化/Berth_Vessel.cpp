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
Berth_Vessel::Berth_Vessel() {
    const char* fileName1 = "Image_Materials\\berth.png";
    char fullPath1[MAX_PATH];
    PathCombineA(fullPath1, currentDirectory, fileName1);
    wchar_t fullPathW[MAX_PATH];
    ConvertToWideChar(fullPath1, fullPathW, MAX_PATH);
    loadimage(&berth, fullPathW);
}
void Berth_Vessel::update(int i, double x, double y) {
    putimagePNG(i*400, 0, &berth);
    string s, s1;
    wstring s_w;
    getline(file, s);
    stringstream ss(s);
    getline(ss, s1, ',');
    getline(ss, s1, ',');
    s_w = wstring(s1.begin(), s1.end());
    settextcolor(BLACK);
    settextstyle(20, 0, L"Consolas");
    outtextxy((i+1) * 400-100, 0, s_w.c_str());
}
void Berth_Vessel::setfile(int x) {
    if (file.is_open())file.close();
    string ch = to_string(x);
    string fileName = "Calculated_Data\\Berth_Vessel" + std::to_string(x) + ".txt";
    const char* fileName1 = fileName.c_str();
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName1);
    file.open(fullPath);
}
Berth_Vessel::~Berth_Vessel() {
    file.close();
}