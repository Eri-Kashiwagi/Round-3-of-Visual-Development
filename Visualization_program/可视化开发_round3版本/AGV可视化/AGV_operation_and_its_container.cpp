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

    const char* fileName2 = "Image_Materials\\agv1.png";
    char fullPath2[MAX_PATH];
    PathCombineA(fullPath2, currentDirectory, fileName2);
    wchar_t fullPathW2[MAX_PATH];
    ConvertToWideChar(fullPath2, fullPathW2, MAX_PATH);
    for (int i = 0; i < 12; i++) {
        loadimage(&AGVPNG1[i], fullPathW2);
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
    getline(ss, s1, ',');
    if (s1=="1"||s1=="2") {
        putimage(x, y, &AGVPNG1[i]);
        if (s1 == "1")settextcolor(BLACK);
        else settextcolor(RED);
        getline(ss, s1);
        wstring s_w = wstring(s1.begin(), s1.end());
        settextstyle(13, 0, L"Tahoma");
        outtextxy(x+7,y+20+3, s_w.c_str());
        settextcolor(BLACK);
        string s2 = to_string(i);
        s2 = "AGV" + s2;
        s_w = wstring(s2.begin(), s2.end());
        settextstyle(11, 0, L"Tahoma");
        outtextxy(x + 16, y + 20 + 27, s_w.c_str());
        settextcolor(BLACK);
    }
    else {
        putimage(x, y, &AGVPNG[i]);
        string s2 = to_string(i);
        s2 = "AGV" + s2;
        wstring s_w = wstring(s2.begin(), s2.end());
        settextstyle(11, 0, L"Tahoma");
        outtextxy(x + 16, y + 20 + 27, s_w.c_str());
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
