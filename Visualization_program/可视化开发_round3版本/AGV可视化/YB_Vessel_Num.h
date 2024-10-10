#pragma once
#include <iostream>
#include <fstream>   
#include <graphics.h> 
#include "ControlPoint.h"
class YB_Vessel_Num {
public:
    std::ifstream file;
    void update(int i, double x, double y);
    YB_Vessel_Num();
    ~YB_Vessel_Num();
};
