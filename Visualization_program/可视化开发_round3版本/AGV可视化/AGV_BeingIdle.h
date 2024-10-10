#pragma once
#include <iostream>
#include <fstream>   
#include <graphics.h> 
#include "ControlPoint.h"
class AGV_BeingIdle {
public:
    std::ifstream file;
    void update(int i, double x, double y);
    AGV_BeingIdle();
    ~AGV_BeingIdle();
};
