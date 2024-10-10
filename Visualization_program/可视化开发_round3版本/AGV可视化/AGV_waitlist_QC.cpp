#include "AGV_waitlist_QC.h"
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <string>
#include <sstream> 
#include <windows.h>
#include <shlwapi.h>
using namespace std;
AGV_waitlist_QC::AGV_waitlist_QC() {
    char currentDirectory[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, currentDirectory);
    for (int i = 0; i < 3; ++i) {
        PathRemoveFileSpecA(currentDirectory);
    }
    const char* fileName = "Calculated_Data\\AGV_waitlist_QC.txt";
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName);
    file.open(fullPath);
}
void AGV_waitlist_QC::update(int i, double x, double y) {
    string s,s1;
    wstring s_w;
    getline(file, s);
    stringstream ss(s);
    getline(ss, s1, ',');
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
AGV_waitlist_QC::~AGV_waitlist_QC() {
    file.close();
}