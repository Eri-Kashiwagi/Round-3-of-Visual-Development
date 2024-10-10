#pragma once
#include <iostream>
#include <fstream>   
#include <graphics.h> 
#include "ControlPoint.h"
class AGV_operation_and_its_container {
public:
    ControlPoint cp[12];
    std::ifstream file; 
    IMAGE AGVPNG[12]; 
    void update(int i, double x, double y);
    AGV_operation_and_its_container();
    ~AGV_operation_and_its_container();
};
