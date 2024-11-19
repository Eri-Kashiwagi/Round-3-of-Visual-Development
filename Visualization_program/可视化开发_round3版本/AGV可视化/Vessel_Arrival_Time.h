#pragma once
#include <iostream>
#include <fstream>   
#include <graphics.h> 
#include "ControlPoint.h"
#include "Directory.h"
class Vessel_Arrival_Time :public Directory{
public:
    std::ifstream file;
    std::wstring arrive_time[300];
    std::wstring vessel_id[300];
    std::time_t current_time_t[300];
    void update(int i, time_t temp);
	Vessel_Arrival_Time();
	~Vessel_Arrival_Time();
};