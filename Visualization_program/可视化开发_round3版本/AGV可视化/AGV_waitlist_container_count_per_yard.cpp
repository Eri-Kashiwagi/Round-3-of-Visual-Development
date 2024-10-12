#include "AGV_waitlist_container_count_per_yard.h"
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <string>
#include <sstream> 
#include <windows.h>
#include <shlwapi.h>
using namespace std;
#pragma comment(lib, "Shlwapi.lib")
AGV_waitlist_container_count_per_yard::AGV_waitlist_container_count_per_yard() {
}
void AGV_waitlist_container_count_per_yard::update(int i,double x,double y) {
    string s,s1;
    getline(file, s);
    stringstream ss(s);
    getline(ss, s1, ',');
    getline(ss, s1, ',');
    wstring s_w = L"Contains:" + wstring(s1.begin(), s1.end());
    settextstyle(25, 0, L"Tahoma");
    outtextxy(x - 25, y + 120, s_w.c_str());
    int d = 1;
    while (getline(ss, s1, ',')) {
        if (d % 2 != 0) {
            s_w = wstring(s1.begin(), s1.end());
            getline(ss, s1, ',');
            if (s1 == "1")settextcolor(BLACK);
            else settextcolor(RED);
            settextstyle(15, 0, L"Tahoma");
            outtextxy(x - 25 + 7, y + 150 + (d - 1) / 2 * 20, s_w.c_str());
            settextcolor(BLACK);
        }
        else {
            s_w = wstring(s1.begin(), s1.end());
            getline(ss, s1, ',');
            if (s1 == "1")settextcolor(BLACK);
            else settextcolor(RED);
            settextstyle(15, 0, L"Tahoma");
            outtextxy(x - 25 + 50, y + 150 + (d - 1) / 2 * 20, s_w.c_str());
            settextcolor(BLACK);
        }
        d++;
    }
}
void AGV_waitlist_container_count_per_yard::setfile(int x) {
    if (file.is_open())file.close();
    string ch = to_string(x);
    string fileName = "Calculated_Data\\AGV_waitlist_container_count_per_yard" + std::to_string(x) + ".txt";
    const char* fileName1 = fileName.c_str();
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName1);
    file.open(fullPath);
}
AGV_waitlist_container_count_per_yard::~AGV_waitlist_container_count_per_yard() {
    file.close();
}
