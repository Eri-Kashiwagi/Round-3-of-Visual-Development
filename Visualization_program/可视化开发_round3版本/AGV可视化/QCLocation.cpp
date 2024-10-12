#include "QCLocation.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <shlwapi.h>
using namespace std;
inline void ConvertToWideChar(const char* src, wchar_t* dest, int destSize) {
    MultiByteToWideChar(CP_ACP, 0, src, -1, dest, destSize);
}
QCLocation::QCLocation() {
    const char* fileName = "Calculated_Data\\QCLocation.txt";
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName);
    file.open(fullPath);

    char currentDirectory1[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, currentDirectory1);
    for (int i = 0; i < 3; ++i) {
        PathRemoveFileSpecA(currentDirectory1);
    }
    const char* fileName1 = "Image_Materials\\qc.png";
    char fullPath1[MAX_PATH];
    PathCombineA(fullPath1, currentDirectory1, fileName1);
    wchar_t fullPathW[MAX_PATH];
    ConvertToWideChar(fullPath1, fullPathW, MAX_PATH);
    for (int i = 0; i < 12; i++) {
        loadimage(&QCPNG[i], fullPathW);
        file >> cp[i].x >> cp[i].y;
    }
}

QCLocation::~QCLocation() {
    file.close();
}
