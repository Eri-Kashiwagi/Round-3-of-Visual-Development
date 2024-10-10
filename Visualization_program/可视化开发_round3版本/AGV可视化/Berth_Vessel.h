#pragma once
#include <iostream>
#include <fstream>   
#include <graphics.h> 
class Berth_Vessel {
public:
    std::ifstream file;
    IMAGE berth;
    Berth_Vessel();
    void update(int i, double x, double y);
    ~Berth_Vessel();
};
