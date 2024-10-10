#pragma once
#include <iostream>
#include <fstream>   
#include <graphics.h> 
#include "ControlPoint.h"
class YBLocation {
public:
	ControlPoint cp[16];
	std::ifstream file;
	YBLocation();
	~YBLocation();
};