#pragma once
#include <stdlib.h>
#include <cmath>
#include "glew.h"
#include "glut.h"
#include "GL.H"

class Cuboid
{
	bool isObjectCreated = false;
	double red = 1.0;
	double green = 1.0;
	double blue = 1.0;
public:
	void create(double size_x, double size_y, double size_z, double offset_x, double offset_y, double offset_z);
	void setColor(double red, double green, double blue);
};

