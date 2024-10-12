#pragma once
#include <iostream>
#include <fstream>   
#include <graphics.h> 
#include "Directory.h"
class Berth_Vessel:public Directory {
public:
    std::ifstream file;
    IMAGE berth;
    Berth_Vessel();
    void update(int i, double x, double y);
    void setfile(int x);
    ~Berth_Vessel();
};
