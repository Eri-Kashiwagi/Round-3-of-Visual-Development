#pragma once
#include "Directory.h"
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <string>
#include <sstream> 
#include <shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
Directory::Directory() {
    GetCurrentDirectoryA(MAX_PATH, currentDirectory);
    for (int i = 0; i < 3; ++i) {
        PathRemoveFileSpecA(currentDirectory);
    }
}
Directory::~Directory() {
}