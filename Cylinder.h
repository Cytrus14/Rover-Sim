#pragma once
#include <stdlib.h>
#include <cmath>
#include "glew.h"
#include "glut.h"
#include "GL.H"
class Cylinder
{
	bool isObjectCreated = false;
	double red = 1.0;
	double green = 1.0;
	double blue = 1.0;
public:
	void create(int resolution, int orientation, double height, double width, double offset_x, double offset_y, double offset_z);
	void setColor(double red, double green, double blue);
};

