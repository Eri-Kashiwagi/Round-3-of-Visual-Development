#pragma once
#include <iostream>
#include <fstream>   
#include <graphics.h> 
#include "Directory.h"
class Change_Speed :public Directory {
public:
	IMAGE pg[8];
	int tt = 0;
	Change_Speed();
	void change(ExMessage msg);
	void update(int i, double x, double y);
	~Change_Speed();
};