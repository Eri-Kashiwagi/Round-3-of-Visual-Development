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
void YB_Vessel_Num::setfile(int x) {
    if (file.is_open())file.close();
    string ch = to_string(x);
    string fileName = "Calculated_Data\\YB_Vessel_Num" + std::to_string(x) + ".txt";
    const char* fileName1 = fileName.c_str();
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName1);
    file.open(fullPath);
}
YB_Vessel_Num::~YB_Vessel_Num() {
    file.close();
}