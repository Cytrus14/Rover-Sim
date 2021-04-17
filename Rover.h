#pragma once
#include "Wheel.h";
#include "Body.h"
#include "SideAxis.h"

class Rover
{
	Wheel* wheels;
	Body* body;
	SideAxis* sideAxis;
public:
	void create();
	~Rover();
};

