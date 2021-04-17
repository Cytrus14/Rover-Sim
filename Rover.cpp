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

	cubes = new Cuboid[4];
	cubes[0].setColor(0.5, 0.9, 0.9);
	cubes[1].setColor(0.5, 0.9, 0.9);
	cubes[2].setColor(0.5, 0.9, 0.9);
	cubes[3].setColor(0.5, 0.9, 0.9);
	cubes[0].create(0.4, 0.4, 0.4, 1.1, 0.9, -0.8);
	cubes[1].create(0.4, 0.4, 0.4, 3, 0.9, -0.8);
	cubes[2].create(0.4, 0.4, 0.4, 1.1, 0.9, -4.1);
	cubes[3].create(0.4, 0.4, 0.4, 3, 0.9, -4.1);

	mainAxis = new Cylinder[2];
	mainAxis[0].setColor(0, 0, 1);
	mainAxis[1].setColor(0, 0, 1);
	mainAxis[0].create(3, 1, 3.5, 0.1, 1.3, 1.1, -4);
	mainAxis[1].create(3, 1, 3.5, 0.1, 3.2, 1.1, -4);

	mainMount = new Cylinder;
	mainMount->setColor(0.5, 1.0, 0);
	mainMount->create(50, 2, 3, 0.2, 0.7, 1.2, -2.9);

	head = new Cuboid;
	head->setColor(0.4, 0.4, 0.9);
	head->create(0.5, 0.8, 1.5, 0.4, 4, -3.5);

	camera = new Cylinder;
	camera->setColor(0.2, 0.4, 0.5);
	camera->create(10, 3, 0.2, 0.3, 0.2, 4.4, -2.5);


}

Rover::~Rover()
{
	delete[] wheels;
	delete[] body;
	delete[] sideAxis;
	delete[] cubes;
	delete[] mainAxis;
	delete mainMount;
	delete head;
	delete camera;
}
