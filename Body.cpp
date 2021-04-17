#include "Body.h"

void Body::create(double offset_x, double offset_y, double offset_z)
{
	if (!isObjectCreated)
	{
		//bottom
		glColor3f(0.5, 0.5, 0.5);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0 + offset_x, 0 + offset_y, 0 + offset_z);
		glVertex3f(x + offset_x, 0 + offset_y, 0 + offset_z);
		glVertex3f(0 + offset_x, 0 + offset_y, z + offset_z);
		glVertex3f(x + offset_x, 0 + offset_y, z + offset_z);
		glEnd();

		//top
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0 + offset_x, y + offset_y, 0 + offset_z);
		glVertex3f(x + offset_x, y + offset_y, 0 + offset_z);
		glVertex3f(0 + offset_x, y + offset_y, z + offset_z);
		glVertex3f(x + offset_x, y + offset_y, z + offset_z);
		glEnd();

		//side a
		glColor3f(0.6, 0.6, 0.6);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0 + offset_x, 0 + offset_y, 0 + offset_z);
		glVertex3f(0 + offset_x, y + offset_y, 0 + offset_z);
		glVertex3f(x + offset_x, 0 + offset_y, 0 + offset_z);
		glVertex3f(x + offset_x, y + offset_y, 0 + offset_z);
		glEnd();

		//side b
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0 + offset_x, 0 + offset_y, 0 + offset_z);
		glVertex3f(0 + offset_x, y + offset_y, 0 + offset_z);
		glVertex3f(0 + offset_x, 0 + offset_y, z + offset_z);
		glVertex3f(0 + offset_x, y + offset_y, z + offset_z);
		glEnd();

		//side c
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0 + offset_x, 0 + offset_y, z + offset_z);
		glVertex3f(0 + offset_x, y + offset_y, z + offset_z);
		glVertex3f(x + offset_x, 0 + offset_y, z + offset_z);
		glVertex3f(x + offset_x, y + offset_y, z + offset_z);
		glEnd();

		//side d
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(x + offset_x, 0 + offset_y, 0 + offset_z);
		glVertex3f(x + offset_x, y + offset_y, 0 + offset_z);
		glVertex3f(x + offset_x, 0 + offset_y, z + offset_z);
		glVertex3f(x + offset_x, y + offset_y, z + offset_z);
		glEnd();


		isObjectCreated = true;
	}
}
