#include "MainAxis.h"

void MainAxis::create(double offset_x, double offset_y, double offset_z)
{
	double x, y, alpha;
	double z = -3.5;
	double PI = 3.1415926536;

	if (!isObjectCreated)
	{
		glColor3f(0, 0, 1);
		//creating base 1
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0 + offset_x, 0 + offset_y, 0 + offset_z);
		for (alpha = 0; alpha <= 2 * PI; alpha += PI / 3)
		{
			x = 0.1 * sin(alpha);
			y = 0.1 * cos(alpha);
			glVertex3f(x + offset_x, y + offset_y, 0 + offset_z);
		}
		glEnd();

		//creating side faces
		glBegin(GL_TRIANGLE_STRIP);
		for (alpha = 0; alpha <= 2 * PI; alpha += PI / 3)
		{
			x = 0.1 * sin(alpha);
			y = 0.1 * cos(alpha);
			glVertex3f(x + offset_x, y + offset_y, 0 + offset_z);
			glVertex3f(x + offset_x, y + offset_y, z + offset_z);
		}
		glEnd();

		//creating base 2
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0 + offset_x, 0 + offset_y, z + offset_z);
		for (alpha = 0; alpha <= 2 * PI; alpha += PI / 3)
		{
			x = 0.1 * sin(alpha);
			y = 0.1 * cos(alpha);
			glVertex3f(x + offset_x, y + offset_y, z + offset_z);
		}
		glEnd();
	}
	isObjectCreated = true;

}
