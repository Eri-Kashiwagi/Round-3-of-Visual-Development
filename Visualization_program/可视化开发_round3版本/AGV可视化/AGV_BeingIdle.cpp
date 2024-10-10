#include "AGV_BeingIdle.h"
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <string>
#include <sstream> 
#include <windows.h>
#include <shlwapi.h>
using namespace std;
#pragma comment(lib, "Shlwapi.lib")
AGV_BeingIdle::AGV_BeingIdle() {
    char currentDirectory[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, currentDirectory); 
    for (int i = 0; i < 3; ++i) {
        PathRemoveFileSpecA(currentDirectory);  
    }
    const char* fileName = "Calculated_Data\\AGV_BeingIdle.txt";
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName); 
    file.open(fullPath);
}
void AGV_BeingIdle::update(int i, double x, double y) {
    string s;
    getline(file, s,',');
    getline(file, s,',');
    s = "AGV_BeingIdle: " + s;
    wstring s_w = wstring(s.begin(), s.end());
    settextcolor(BLACK);
    settextstyle(50, 0, L"Consolas");
    outtextxy(50, 950, s_w.c_str());
}
AGV_BeingIdle::~AGV_BeingIdle() {
    file.close();
}