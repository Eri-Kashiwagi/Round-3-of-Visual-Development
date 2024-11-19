#include "Vessel_Arrival_Time.h"
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <string>
#include <sstream> 
#include <windows.h>
#include <shlwapi.h>
#include <ctime>
#include <iomanip>
using namespace std;
inline void ConvertToWideChar(const char* src, wchar_t* dest, int destSize) {
    MultiByteToWideChar(CP_ACP, 0, src, -1, dest, destSize);
}
Vessel_Arrival_Time::Vessel_Arrival_Time() {
    if (file.is_open())file.close();
    string fileName = "Calculated_Data\\vessel_arrival_time.txt";
    const char* fileName1 = fileName.c_str();
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName1);
    file.open(fullPath);
    for (int j = 0; j < 300; j++) {
        string s, s1;
        wstring s_w;
        getline(file, s);
        stringstream ss(s);
        getline(ss, s1, ',');
        string s2 = s1.substr(8);
        vessel_id[j] = wstring(s2.begin(), s2.end());
        getline(ss, s1, ',');
        getline(ss, s1, ',');
        s2 = s1.substr(14);
        arrive_time[j] = wstring(s2.begin(), s2.end());
        istringstream sss(s2);
        tm current_time;
        sss >> std::get_time(&current_time, "%Y-%m-%d %H:%M:%S");
        current_time_t[j] = mktime(&current_time);
    }
}
void Vessel_Arrival_Time::update(int i,time_t temp) {
    for (int j = 0; j < 300; j++) {
        if (current_time_t[j] > temp) {
            int y = 0;
            string s1 = "Vessel_Arrival_Next:";
            wstring s_w=wstring(s1.begin(), s1.end());
            settextstyle(15, 0, L"Tahoma");
            setfillcolor(WHITE);
            solidrectangle(1570-5, 670, 1690, 725);
            outtextxy(1570-5+1+7, 670, s_w.c_str());
            outtextxy(1570-5+20+18, 690, vessel_id[j].c_str());
            outtextxy(1570-5, 710, arrive_time[j].c_str());
            return;
        }
    }
}
Vessel_Arrival_Time::~Vessel_Arrival_Time() {
    file.close();
}