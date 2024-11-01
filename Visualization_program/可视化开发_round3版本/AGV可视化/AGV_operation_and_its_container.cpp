#include "AGV_operation_and_its_container.h"
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <string>
#include <sstream> 
#include <windows.h>
#include <shlwapi.h>
using namespace std;
#pragma comment(lib, "Shlwapi.lib")
inline void ConvertToWideChar(const char* src, wchar_t* dest, int destSize) {
    MultiByteToWideChar(CP_ACP, 0, src, -1, dest, destSize);
}
AGV_operation_and_its_container::AGV_operation_and_its_container() {
    const char* fileName1 = "Image_Materials\\agv.png";
    char fullPath1[MAX_PATH];
    PathCombineA(fullPath1, currentDirectory, fileName1);
    wchar_t fullPathW[MAX_PATH];
    ConvertToWideChar(fullPath1, fullPathW, MAX_PATH);
    for (int i = 0; i < 12; i++) {
        loadimage(&AGVPNG[i], fullPathW);
    }
}
void AGV_operation_and_its_container::update(int i, double x, double y) {
    string s,s1;
    getline(file, s);
    stringstream ss(s);
    getline(ss, s1, ',');
    getline(ss, s1, ',');
    x = stod(s1);
    getline(ss, s1, ',');
    y = stod(s1);
    y += 50+20;
    putimage(x,y, &AGVPNG[i]);
    getline(ss, s1, ',');
    if (s1=="1"||s1=="2") {
        if (s1 == "1")settextcolor(BLACK);
        else settextcolor(RED);
        getline(ss, s1);
        wstring s_w = wstring(s1.begin(), s1.end());
        settextstyle(20, 0, L"Tahoma");
        outtextxy(x,y+20+20, s_w.c_str());
        settextcolor(BLACK);
    }
}
void AGV_operation_and_its_container::setfile(int x) {
    if (file.is_open())file.close();
    string ch = to_string(x);
    string fileName = "Calculated_Data\\AGV_operation_and_its_container" + std::to_string(x) + ".txt";
    const char* fileName1 = fileName.c_str();
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName1);
    file.open(fullPath);
}
AGV_operation_and_its_container::~AGV_operation_and_its_container() {
    file.close();
}
