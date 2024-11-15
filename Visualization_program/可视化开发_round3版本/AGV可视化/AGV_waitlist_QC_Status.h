#pragma once
#include <iostream>
#include <fstream>   
#include <graphics.h> 
#include "Directory.h"
#include <unordered_map>
using namespace std;
class AGV_waitlist_QC_Status :public Directory {
public:
    std::ifstream file;
    IMAGE status[9],quayside;
    AGV_waitlist_QC_Status();
    unordered_map<int, string>mp;
    unordered_map<string, int> imagemp;
    void update(int i, double x, double y);
    void unzip_use_file(int x);
    void unzip_file(int x);
    void use_file(int x);
    ~AGV_waitlist_QC_Status();
};
