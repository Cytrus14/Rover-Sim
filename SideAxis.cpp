#include "SideAxis.h"

void SideAxis::create(double offset_x, double offset_y, double offset_z, double sideOffset)
{
	if (!isObjectCreated)
	{
		//bottom
		glColor3d(1.0, 1.0, 0);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0 + offset_x, 0 + offset_y, 0 + offset_z);
		glVertex3f(x + offset_x, 0 + offset_y, 0 + offset_z);
		glVertex3f(0 + offset_x, 0 + offset_y, z + offset_z);
		glVertex3f(x + offset_x, 0 + offset_y, z + offset_z);
		glEnd();

		//top
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(sideOffset + 0 + offset_x, y + offset_y, 0 + offset_z);
		glVertex3f(sideOffset + x + offset_x, y + offset_y, 0 + offset_z);
		glVertex3f(sideOffset + 0 + offset_x, y + offset_y, z + offset_z);
		glVertex3f(sideOffset + x + offset_x, y + offset_y, z + offset_z);
		glEnd();

		//side a
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0 + offset_x, 0 + offset_y, 0 + offset_z);
		glVertex3f(sideOffset + 0 + offset_x, y + offset_y, 0 + offset_z);
		glVertex3f(x + offset_x, 0 + offset_y, 0 + offset_z);
		glVertex3f(sideOffset + x + offset_x, y + offset_y, 0 + offset_z);
		glEnd();

		//side b
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0 + offset_x, 0 + offset_y, 0 + offset_z);
		glVertex3f(sideOffset + 0 + offset_x, y + offset_y, 0 + offset_z);
		glVertex3f(0 + offset_x, 0 + offset_y, z + offset_z);
		glVertex3f(sideOffset + 0 + offset_x, y + offset_y, z + offset_z);
		glEnd();

		//side c
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0 + offset_x, 0 + offset_y, z + offset_z);
		glVertex3f(sideOffset + 0 + offset_x, y + offset_y, z + offset_z);
		glVertex3f(x + offset_x, 0 + offset_y, z + offset_z);
		glVertex3f(sideOffset + x + offset_x, y + offset_y, z + offset_z);
		glEnd();

		//side d
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(x + offset_x, 0 + offset_y, 0 + offset_z);
		glVertex3f(sideOffset + x + offset_x, y + offset_y, 0 + offset_z);
		glVertex3f(x + offset_x, 0 + offset_y, z + offset_z);
		glVertex3f(sideOffset + x + offset_x, y + offset_y, z + offset_z);
		glEnd();

		isObjectCreated = true;
	}
}
