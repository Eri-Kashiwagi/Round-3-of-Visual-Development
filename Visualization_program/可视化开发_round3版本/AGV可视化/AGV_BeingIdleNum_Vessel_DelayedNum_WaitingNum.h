#pragma once
#include <iostream>
#include <fstream>   
#include <graphics.h> 
#include "ControlPoint.h"
#include "Directory.h"
class AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum:public Directory {
public:
    std::ifstream file;
    void update(int i, double x, double y);
    void unzip_use_file(int x);
    void unzip_file(int x);
    void use_file(int x);
    AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum();
    ~AGV_BeingIdleNum_Vessel_DelayedNum_WaitingNum();
};
