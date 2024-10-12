#pragma once
#include <iostream>
#include <fstream>   
#include <graphics.h> 
#include "ControlPoint.h"
#include "Directory.h"
class AGV_BeingIdleNum_Vessel_DelayedNum:public Directory {
public:
    std::ifstream file;
    void update(int i, double x, double y);
    void setfile(int x);
    AGV_BeingIdleNum_Vessel_DelayedNum();
    ~AGV_BeingIdleNum_Vessel_DelayedNum();
};
