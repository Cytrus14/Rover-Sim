#include "Cylinder.h"

void Cylinder::create(int resolution, int orientation, double height, double width, double offset_x, double offset_y, double offset_z)
{
	double x, y, z, alpha;
	double PI = 3.1415926536;

	if (!isObjectCreated)
	{
		glColor3f(red, green, blue);
		switch (orientation)
		{
		case 1:
			//creating base 1
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0 + offset_x, 0 + offset_y, 0 + offset_z);
			for (alpha = 0; alpha <= 2 * PI; alpha += PI / resolution)
			{
				x = width * sin(alpha);
				y = width * cos(alpha);
				glVertex3f(x + offset_x, y + offset_y, 0 + offset_z);
			}
			glEnd();

			//creating side faces
			glBegin(GL_TRIANGLE_STRIP);
			for (alpha = 0; alpha <= 2 * PI; alpha += PI / resolution)
			{
				x = width * sin(alpha);
				y = width * cos(alpha);
				glVertex3f(x + offset_x, y + offset_y, 0 + offset_z);
				glVertex3f(x + offset_x, y + offset_y, height + offset_z);
			}
			glEnd();

			//creating base 2
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0 + offset_x, 0 + offset_y, height + offset_z);
			for (alpha = 0; alpha <= 2 * PI; alpha += PI / resolution)
			{
				x = width * sin(alpha);
				y = width * cos(alpha);
				glVertex3f(x + offset_x, y + offset_y, height + offset_z);
			}
			glEnd();
			isObjectCreated = true;
			break;
		case 2:
			//creating base 1
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0 + offset_x, 0 + offset_y, 0 + offset_z);
			for (alpha = 0; alpha <= 2 * PI; alpha += PI / resolution)
			{
				x = width * sin(alpha);
				z = width * cos(alpha);
				glVertex3f(x + offset_x, 0 + offset_y, z + offset_z);
			}
			glEnd();

			//creating side faces
			glBegin(GL_TRIANGLE_STRIP);
			for (alpha = 0; alpha <= 2 * PI; alpha += PI / resolution)
			{
				x = width * sin(alpha);
				z = width * cos(alpha);
				glVertex3f(x + offset_x, 0 + offset_y, z + offset_z);
				glVertex3f(x + offset_x, height + offset_y, z + offset_z);
			}
			glEnd();

			//creating base 2
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0 + offset_x, height + offset_y, 0 + offset_z);
			for (alpha = 0; alpha <= 2 * PI; alpha += PI / resolution)
			{
				x = width * sin(alpha);
				z = width * cos(alpha);
				glVertex3f(x + offset_x, height + offset_y, z + offset_z);
			}
			glEnd();
			isObjectCreated = true;
			break;
		case 3:
			//creating base 1
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0 + offset_x, 0 + offset_y, 0 + offset_z);
			for (alpha = 0; alpha <= 2 * PI; alpha += PI / resolution)
			{
				y = width * sin(alpha);
				z = width * cos(alpha);
				glVertex3f(0 + offset_x, y + offset_y, z + offset_z);
			}
			glEnd();

			//creating side faces
			glBegin(GL_TRIANGLE_STRIP);
			for (alpha = 0; alpha <= 2 * PI; alpha += PI / resolution)
			{
				y = width * sin(alpha);
				z = width * cos(alpha);
				glVertex3f(0 + offset_x, y + offset_y, z + offset_z);
				glVertex3f(height + offset_x, y + offset_y, z + offset_z);
			}
			glEnd();

			//creating base 2
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(height + offset_x, 0 + offset_y, 0 + offset_z);
			for (alpha = 0; alpha <= 2 * PI; alpha += PI / resolution)
			{
				y = width * sin(alpha);
				z = width * cos(alpha);
				glVertex3f(height + offset_x, y + offset_y, z + offset_z);
			}
			glEnd();
			isObjectCreated = true;
			break;
		}
	}
}

void Cylinder::setColor(double red, double green, double blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}
