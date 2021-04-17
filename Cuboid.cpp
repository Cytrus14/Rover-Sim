#include "Cuboid.h"

void Cuboid::create(double size_x, double size_y, double size_z, double offset_x, double offset_y, double offset_z)
{
	if (!isObjectCreated)
	{
		//bottom
		glColor3f(red, green, blue);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0 + offset_x, 0 + offset_y, 0 + offset_z);
		glVertex3f(size_x + offset_x, 0 + offset_y, 0 + offset_z);
		glVertex3f(0 + offset_x, 0 + offset_y, size_z + offset_z);
		glVertex3f(size_x + offset_x, 0 + offset_y, size_z + offset_z);
		glEnd();

		//top
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0 + offset_x, size_y + offset_y, 0 + offset_z);
		glVertex3f(size_x + offset_x, size_y + offset_y, 0 + offset_z);
		glVertex3f(0 + offset_x, size_y + offset_y, size_z + offset_z);
		glVertex3f(size_x + offset_x, size_y + offset_y, size_z + offset_z);
		glEnd();

		//side a
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0 + offset_x, 0 + offset_y, 0 + offset_z);
		glVertex3f(0 + offset_x, size_y + offset_y, 0 + offset_z);
		glVertex3f(size_x + offset_x, 0 + offset_y, 0 + offset_z);
		glVertex3f(size_x + offset_x, size_y + offset_y, 0 + offset_z);
		glEnd();

		//side b
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0 + offset_x, 0 + offset_y, 0 + offset_z);
		glVertex3f(0 + offset_x, size_y + offset_y, 0 + offset_z);
		glVertex3f(0 + offset_x, 0 + offset_y, size_z + offset_z);
		glVertex3f(0 + offset_x, size_y + offset_y, size_z + offset_z);
		glEnd();

		//side c
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0 + offset_x, 0 + offset_y, size_z + offset_z);
		glVertex3f(0 + offset_x, size_y + offset_y, size_z + offset_z);
		glVertex3f(size_x + offset_x, 0 + offset_y, size_z + offset_z);
		glVertex3f(size_x + offset_x, size_y + offset_y, size_z + offset_z);
		glEnd();

		//side d
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(size_x + offset_x, 0 + offset_y, 0 + offset_z);
		glVertex3f(size_x + offset_x, size_y + offset_y, 0 + offset_z);
		glVertex3f(size_x + offset_x, 0 + offset_y, size_z + offset_z);
		glVertex3f(size_x + offset_x, size_y + offset_y, size_z + offset_z);
		glEnd();

		isObjectCreated = true;
	}
}

void Cuboid::setColor(double red, double green, double blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}
