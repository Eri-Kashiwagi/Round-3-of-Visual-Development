#pragma once
#include <iostream>
#include <fstream>   
#include <graphics.h> 
#include "Directory.h"
class Berth_Vessel:public Directory {
public:
    std::ifstream file;
    IMAGE vessel,berth;
    Berth_Vessel();
    void update(int i, double x, double y);
    void unzip_use_file(int x);
    void unzip_file(int x);
    void use_file(int x);
    ~Berth_Vessel();
};
