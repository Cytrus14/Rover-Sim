#include <Windows.h>
#include <stdlib.h>
#include <cmath>
#include "glew.h"
#include "glut.h"
#include "GL.H"

// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f, ly = 0.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f, y = 0.0f;

float red, green, blue;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(60.0f, ratio, 0.1f, 500.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}


void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.3f;

	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.03f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.03f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	case GLUT_KEY_PAGE_UP:
		ly += 0.03f;
		break;
	case GLUT_KEY_PAGE_DOWN:
		ly -= 0.03f;
		break;
	}
}

void cegla(double x, double y, double z)
{
	glColor3f(0.7, 0.13, 0.13);

	//gora
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0 + x, 0 + y, 0 + z);
	glVertex3f(0 + x, 12 + y, 0 + z);
	glVertex3f(24 + x, 0 + y, 0 + z);
	glVertex3f(24 + x, 12 + y, 0 + z);
	glEnd();

	//dol
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(24 + x, 0 + y, 6 + z);
	glVertex3f(24 + x, 12 + y, 6 + z);
	glVertex3f(0 + x, 0 + y, 6 + z);
	glVertex3f(0 + x, 12 + y, 6 + z);
	glEnd();

	//bok a
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(24 + x, 0 + y, 0 + z);
	glVertex3f(24 + x, 0 + y, 6 + z);
	glVertex3f(0 + x, 0 + y, 0 + z);
	glVertex3f(0 + x, 0 + y, 6 + z);
	glEnd();

	//bok b
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0 + x, 12 + y, 0 + z);
	glVertex3f(0 + x, 12 + y, 6 + z);
	glVertex3f(24 + x, 12 + y, 0 + z);
	glVertex3f(24 + x, 12 + y, 6 + z);
	glEnd();

	//bok c
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0 + x, 0 + y, 0 + z);
	glVertex3f(0 + x, 0 + y, 6 + z);
	glVertex3f(0 + x, 12 + y, 0 + z);
	glVertex3f(0 + x, 12 + y, 6 + z);
	glEnd();

	//bok d
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(24 + x, 12 + y, 0 + z);
	glVertex3f(24 + x, 12 + y, 6 + z);
	glVertex3f(24 + x, 0 + y, 0 + z);
	glVertex3f(24 + x, 0 + y, 6 + z);
	glEnd();
}


void renderScene(void) {

	// Clear Color and Depth Buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);

	cegla(0,0,-100);

	glutSwapBuffers();
}


int main(int argc, char** argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 640);
	glutCreateWindow("Lighthouse3D- GLUT Tutorial");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	// here are the new entries
	glutSpecialFunc(processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}