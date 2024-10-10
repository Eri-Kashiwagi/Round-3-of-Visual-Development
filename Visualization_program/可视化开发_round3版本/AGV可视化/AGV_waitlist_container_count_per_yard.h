#pragma once
#include <iostream>
#include <fstream>   
#include <graphics.h> 
class AGV_waitlist_container_count_per_yard {
public:
    std::ifstream file;
    AGV_waitlist_container_count_per_yard();
    ~AGV_waitlist_container_count_per_yard();
    void update(int i,double x,double y);
};
