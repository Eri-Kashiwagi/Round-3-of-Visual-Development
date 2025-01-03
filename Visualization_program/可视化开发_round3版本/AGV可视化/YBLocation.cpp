#include "YBLocation.h"
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <windows.h>
#include <shlwapi.h>
YBLocation::YBLocation() {
    const char* fileName = "Calculated_Data\\YBLocation.txt";
    char fullPath[MAX_PATH];
    PathCombineA(fullPath, currentDirectory, fileName);
    file.open(fullPath);
    for (int i = 0; i < 16; i++) {
        file >> cp[i].x >> cp[i].y;
    }
}

YBLocation::~YBLocation() {
    file.close();
}
