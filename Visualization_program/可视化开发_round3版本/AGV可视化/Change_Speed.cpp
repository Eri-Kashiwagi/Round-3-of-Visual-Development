#include"Change_Speed.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <shlwapi.h>
using namespace std;
inline void ConvertToWideChar(const char* src, wchar_t* dest, int destSize) {
    MultiByteToWideChar(CP_ACP, 0, src, -1, dest, destSize);
}
Change_Speed::Change_Speed() {
    for (int i = 0; i < 8; i++) {
        string fileName = "Image_Materials\\speed" + std::to_string(i) + ".png";
        const char* fileName1 = fileName.c_str();
        char fullPath1[MAX_PATH];
        PathCombineA(fullPath1, currentDirectory, fileName1);
        wchar_t fullPathW[MAX_PATH];
        ConvertToWideChar(fullPath1, fullPathW, MAX_PATH);
        loadimage(&pg[i], fullPathW);
    }
    for (int i = 0; i < 4; i++) {
        string fileName = "Image_Materials\\zhenshu" + std::to_string(i) + ".png";
        const char* fileName1 = fileName.c_str();
        char fullPath1[MAX_PATH];
        PathCombineA(fullPath1, currentDirectory, fileName1);
        wchar_t fullPathW[MAX_PATH];
        ConvertToWideChar(fullPath1, fullPathW, MAX_PATH);
        loadimage(&zs[i], fullPathW);
    }
}
void Change_Speed::update(int i, double x, double y) {
    putimage(775+10, 753+22, &pg[0]);
    putimage(825+10, 753+22, &pg[1]);
    putimage(775+10, 803+22, &pg[2]);
    putimage(825+10, 803+22, &pg[3]);
    putimage(775+10, 703 + 22, &zs[0]);
    putimage(825+10, 703 + 22, &zs[1]);
    if (tt == 1) {
        putimage(775+10, 753+22, &pg[4]);
    }
    else if (tt == 5) {
        putimage(825+10, 753+22, &pg[5]);
    }
    else if (tt == 10) {
        putimage(775+10, 803+22, &pg[6]);
    }
    else if (tt == 100) {
        putimage(825+10, 803+22, &pg[7]);
    }
    if (zhenshu == 1000) {
        putimage(775+10, 703 + 22, &zs[2]);
    }
    else if (zhenshu == 100) {
        putimage(825+10, 703 + 22, &zs[3]);
    }
    if (i == 0) {
        settextcolor(BLACK);
        settextstyle(40, 0, L"Consolas");
        string s = "Now_Speed:" + to_string(tt) + "X";
        wstring s_w = wstring(s.begin(), s.end());
        outtextxy(50, 980+12, s_w.c_str());
    }
}
void Change_Speed::change(ExMessage msg) {
    if (msg.message == WM_LBUTTONDOWN) {
        if (msg.x >= 775+10 && msg.x <= 815+10 && msg.y >= 753+22 && msg.y <= 793+22) {
            tt = 1;
            zhenshu = 0;
        }
        else if (msg.x >= 825+10 && msg.x <= 865+10&& msg.y >= 753 + 22 && msg.y <= 793 + 22) {
            tt = 5;
        }
        else if (msg.x >= 775+10 && msg.x <= 815+10 && msg.y >= 803 + 22 && msg.y <= 843 + 22) {
            tt = 10;
        }
        else if (msg.x >= 825+10 && msg.x <= 865+10 && msg.y >= 803 + 22 && msg.y <= 843 + 22) {
            tt = 100;
        }
        else if (msg.x >= 775+10 && msg.x <= 815+10 && msg.y >= 703 + 22 && msg.y <= 743 + 22) {
            zhenshu = 1000;
        }
        else if (msg.x >= 825+10 && msg.x <= 865+10 && msg.y >= 703 + 22 && msg.y <= 743 + 22) {
            zhenshu = 100;
        }
    }
}
Change_Speed::~Change_Speed() {
}