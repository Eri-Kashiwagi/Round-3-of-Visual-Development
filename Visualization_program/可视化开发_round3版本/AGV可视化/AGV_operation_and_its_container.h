#pragma once
#include <iostream>
#include <fstream>   
#include <graphics.h> 
#include "ControlPoint.h"
#include "Directory.h"
class AGV_operation_and_its_container:public Directory {
public:
    ControlPoint cp[12];
    std::ifstream file; 
    IMAGE AGVPNG[12],AGVPNG1[12]; 
    void update(int i, double x, double y);
    void setfile(int x);
    AGV_operation_and_its_container();
    ~AGV_operation_and_its_container();
};
