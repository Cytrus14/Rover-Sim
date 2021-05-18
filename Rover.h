#pragma once
#include "Wheel.h";
#include "Body.h"
#include "SideAxis.h"
#include "Cuboid.h"
#include "Cylinder.h"

class Rover
{
	Wheel* wheels;
	Body* body;
	SideAxis* sideAxis;
	Cuboid* cubes;
	Cylinder* mainAxis;
	Cylinder* mainMount;
	Cuboid* head;
	Cylinder* camera;
public:
	void create(float wheels_angle);
	~Rover();
};

