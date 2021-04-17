#include "Rover.h"

void Rover::create()
{
	wheels = new Wheel[6];
	wheels[0].create(0, 0, 0);
	wheels[1].create(2.5, 0, 0);
	wheels[2].create(4, 0, 0);
	wheels[3].create(0, 0, -4);
	wheels[4].create(2.5, 0, -4);
	wheels[5].create(4, 0, -4);

	body = new Body;
	body->create(0, 0.8, -3.5);

	sideAxis = new SideAxis[6];
	sideAxis[0].create(-0.2, 0, -0.7, 1.5);
	sideAxis[1].create(2.35, 0, -0.7, 0.7);
	sideAxis[2].create(3.9, 0, -0.7, -0.7);
	sideAxis[3].create(-0.2, 0, -4, 1.5);
	sideAxis[4].create(2.35, 0, -4, 0.7);
	sideAxis[5].create(3.9, 0, -4, -0.7);

	glTranslatef(0, 1, 0);
	glutSolidSphere(0.1, 20, 20);



}

Rover::~Rover()
{
	delete[] wheels;
	delete[] body;
}
