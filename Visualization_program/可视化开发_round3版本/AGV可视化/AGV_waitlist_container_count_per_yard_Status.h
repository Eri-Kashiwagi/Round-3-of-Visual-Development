#pragma once
#include <iostream>
#include <fstream>   
#include <graphics.h> 
#include "Directory.h"
#include <unordered_map>
using namespace std;
class AGV_waitlist_container_count_per_yard_Status :public Directory {
public:
    std::ifstream file;
    IMAGE status[4];
    unordered_map<int, string>mp;
    unordered_map<string, int> imagemp;
    AGV_waitlist_container_count_per_yard_Status();
    ~AGV_waitlist_container_count_per_yard_Status();
    void update(int i, double x, double y);
    void setfile(int x);
};
