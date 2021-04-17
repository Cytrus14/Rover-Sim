#pragma once
#include <stdlib.h>
#include <cmath>
#include "glew.h"
#include "glut.h"
#include "GL.H"

class SideAxis
{
	bool isObjectCreated = false;
	double x = 0.2;
	double y = 1.1;
	double z = 0.2;
public:
	void create(double offset_x, double offset_y, double offset_z, double sideOffset);
};

