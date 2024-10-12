#pragma once
#include <iostream>
#include <fstream>   
#include <graphics.h> 
#include "ControlPoint.h"
#include "Directory.h"
class QCLocation:public Directory {
public:
	ControlPoint cp[12];
	std::ifstream file;
	IMAGE QCPNG[12];
	QCLocation();
	~QCLocation();
};