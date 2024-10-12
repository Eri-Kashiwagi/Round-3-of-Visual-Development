#pragma once
#include <iostream>
#include <fstream>   
#include <graphics.h> 
#include "ControlPoint.h"
#include "Directory.h"
class YB_Vessel_Num:public Directory {
public:
    std::ifstream file;
    void update(int i, double x, double y);
    void setfile(int x);
    YB_Vessel_Num();
    ~YB_Vessel_Num();
};
