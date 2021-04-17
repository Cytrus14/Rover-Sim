#pragma once
#include <stdlib.h>
#include <cmath>
#include "glew.h"
#include "glut.h"
#include "GL.H"

class MainAxis
{
	bool isObjectCreated = false;
public:
	void create(double offset_x, double offset_y, double offset_z);
};

