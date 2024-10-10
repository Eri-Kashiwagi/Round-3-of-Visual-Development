#include "YB_Vessel_Num.h"
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <string>
#include <sstream> 
#include <windows.h>
#include <shlwapi.h>
using namespace std;
YB_Vessel_Num::YB_Vessel_Num() {
    char currentDirectory[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, currentDirectory);
    for (int i = 0; i < 3; ++i) {
        PathRemoveFileSpecA(currentDirectory);
    }
    const char* fileName = "Calculated_Data\\YB_Vessel_Num.txt";
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName);
    file.open(fullPath);
}
void YB_Vessel_Num::update(int i, double x, double y) {
    string s, s1;
    wstring s_w;
    getline(file, s);
    stringstream ss(s);
    getline(ss, s1, ',');
    int d = 1;
    while (getline(ss, s1, ',')) {
        s_w = wstring(s1.begin(), s1.end());
        settextstyle(13, 0, L"Tahoma");
        outtextxy(x - 25 + 26 * (d % 5), y + 150 + 160 + (d - 1) / 5 * 20, s_w.c_str());
        d++;
    }
}
YB_Vessel_Num::~YB_Vessel_Num() {
    file.close();
}