#pragma once
#include "/Program Files (x86)/EzSoftware UC/AXL(Library)/C, C++/AXL.h"
#include "/Program Files (x86)/EzSoftware UC/AXL(Library)/C, C++/AXM.h"
#include <iostream>

#define DllExport   __declspec( dllexport )
//#include <conio.h>

class DllExport CLinear_actu
{
public:
	CLinear_actu(std::string mot_file);
	~CLinear_actu();
	void move_actu(int pos, int vel_cmd, int accel_cmd);
};

