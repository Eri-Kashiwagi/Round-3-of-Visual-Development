#include "AGV_waitlist_container_count_per_yard_Status.h"
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <string>
#include <sstream> 
#include <windows.h>
#include <shlwapi.h>
#include <unordered_map>
using namespace std;
#pragma comment(lib, "Shlwapi.lib")
inline void ConvertToWideChar(const char* src, wchar_t* dest, int destSize) {
    MultiByteToWideChar(CP_ACP, 0, src, -1, dest, destSize);
}
AGV_waitlist_container_count_per_yard_Status::AGV_waitlist_container_count_per_yard_Status() {
    mp = {
        {0, "YC"},
        {1, "Stacking"},
        {2, "Unstacking"},
        {3, "HoldingonUnstacking"},
    };
    imagemp = {
        {"YC", 0},
        {"Stacking", 1},
        {"Unstacking", 2},
        {"HoldingonUnstacking", 3},
    };
    for (int i = 0; i < 4; i++) {
        string fileName = "Image_Materials\\YC_" + mp[i] + ".png";
        const char* fileName1 = fileName.c_str();
        char fullPath1[MAX_PATH];
        PathCombineA(fullPath1, currentDirectory, fileName1);
        wchar_t fullPathW[MAX_PATH];
        ConvertToWideChar(fullPath1, fullPathW, MAX_PATH);
        loadimage(&status[i], fullPathW);
    }
}
void AGV_waitlist_container_count_per_yard_Status::update(int i, double x, double y) {
    string s, s1;
    getline(file, s);
    stringstream ss(s);
    getline(ss, s1, ',');
    getline(ss, s1, ',');
    wstring s_w = L"Contains:" + wstring(s1.begin(), s1.end());
    settextstyle(25, 0, L"Tahoma");
    outtextxy(x - 25, y + 120, s_w.c_str());
    getline(ss, s1, ',');
    if (i % 2 == 0) {
        putimage(x - 68, y + 98, &status[imagemp[s1]]);
    }
    else {
        putimage(x + 70, y + 98, &status[imagemp[s1]]);
    }
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
void AGV_waitlist_container_count_per_yard_Status::setfile(int x) {
    if (file.is_open())file.close();
    string ch = to_string(x);
    string fileName = "Calculated_Data\\AGV_waitlist_container_count_per_yard_Status" + std::to_string(x) + ".txt";
    const char* fileName1 = fileName.c_str();
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName1);
    file.open(fullPath);
}
AGV_waitlist_container_count_per_yard_Status::~AGV_waitlist_container_count_per_yard_Status() {
    file.close();
}
