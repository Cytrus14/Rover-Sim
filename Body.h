#pragma once
#include <stdlib.h>
#include <cmath>
#include "glew.h"
#include "glut.h"
#include "GL.H"

class Body
{
	bool isObjectCreated = false;
	double x = 4;
	double z = 2.5;
	double y = 0.9;
public:
	void create(double offset_x, double offset_y, double offset_z);
};

	