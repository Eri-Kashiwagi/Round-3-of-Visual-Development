#pragma once
#include <iostream>
#include <fstream>   
#include <graphics.h> 
#include "ControlPoint.h"
class AGV_BeingIdleNum_Vessel_DelayedNum {
public:
    std::ifstream file;
    void update(int i, double x, double y);
    AGV_BeingIdleNum_Vessel_DelayedNum();
    ~AGV_BeingIdleNum_Vessel_DelayedNum();
};
