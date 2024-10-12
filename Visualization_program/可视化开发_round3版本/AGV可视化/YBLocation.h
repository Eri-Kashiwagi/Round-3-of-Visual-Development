#pragma once
#include <iostream>
#include <fstream>   
#include <graphics.h> 
#include "ControlPoint.h"
#include "Directory.h"
class YBLocation:public Directory {
public:
	ControlPoint cp[16];
	std::ifstream file;
	YBLocation();
	~YBLocation();
};