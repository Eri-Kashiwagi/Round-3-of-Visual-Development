#pragma once
#include <iostream>
#include <fstream>   
#include <graphics.h> 
class AGV_waitlist_QC {
public:
    std::ifstream file;
    AGV_waitlist_QC();
    void update(int i,double x,double y);
    ~AGV_waitlist_QC();
};
