#pragma once
#include <iostream>
#include <fstream>   
#include <graphics.h> 
#include "Directory.h"
class AGV_waitlist_QC:public Directory {
public:
    std::ifstream file;
    AGV_waitlist_QC();
    void update(int i,double x,double y);
    void setfile(int x);
    ~AGV_waitlist_QC();
};
