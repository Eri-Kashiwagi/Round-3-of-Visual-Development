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
void AGV_waitlist_QC::setfile(int x) {
    if (file.is_open())file.close();
    string ch = to_string(x);
    string fileName = "Calculated_Data\\AGV_waitlist_QC" + std::to_string(x) + ".txt";
    const char* fileName1 = fileName.c_str();
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName1);
    file.open(fullPath);
}
AGV_waitlist_QC::~AGV_waitlist_QC() {
    file.close();
}