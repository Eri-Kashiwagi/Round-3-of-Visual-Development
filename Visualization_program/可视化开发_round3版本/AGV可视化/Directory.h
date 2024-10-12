#pragma once
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <string>
class Directory {
public:
	Directory();
	char currentDirectory[MAX_PATH];

	~Directory();
};