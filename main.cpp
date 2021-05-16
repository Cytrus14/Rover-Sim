#define radian 57.29578
#include <Windows.h>
#include <math.h>
#include "Rover.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "ObjLoader.h"

float temp = 0;
float temp2 = 0;
// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f, ly = 0.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f, y = 0.0f;

float red, green, blue;

unsigned int textures[4];

//rover coordinates or rotation
float start_pos_x = 0;
float start_pos_z = 0;
float rotation_angle = 0.0;

//rover velocity
float velocity_L = 0.0;
float velocity_R = 0.0;


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
		angle -= 0.1f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.1f;
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
		y += fraction;
		break;
	case GLUT_KEY_PAGE_DOWN:
		y -= fraction;
		break;
	case GLUT_KEY_HOME:
		ly += 0.1f;
		break;
	case GLUT_KEY_END:
		ly -= 0.1f;
		break;
	}
}

void processKeyboardKeys(unsigned char key, int x, int y)
{
	switch (key){
	case 'w':
		velocity_L += 0.1;
		break;
	case 's':
		velocity_L -= 0.1;
		break;
	case 'a':
		rotation_angle += 3;
		break;
	case 'd':
		rotation_angle -= 3;
		break;
	}
}


void renderScene(void) {

	// Clear Color and Depth Buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);

	//creating objects

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	ObjLoader rock1("Objects\\rock.obj");
	rock1.create(0,0,25);
	ObjLoader rock2("Objects\\rock.obj");
	rock2.create(30,-8,-50);
	ObjLoader rock3("Objects\\rock.obj");
	rock3.create(-40,-25,-80);
	ObjLoader rock4("Objects\\rock.obj");
	rock4.create(20,0,10);
	ObjLoader rock5("Objects\\rock.obj");
	rock5.create(-70, -6, 20);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	ObjLoader surface("Objects\\surface.obj");
	surface.create(0,5.5,0);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	ObjLoader artifactBase("Objects\\artifact_base.obj");
	artifactBase.create(-125,-35,-180);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	ObjLoader artifactRods("Objects\\artifact_rods.obj");
	artifactRods.create(-125, -35, -180);

	glBindTexture(GL_TEXTURE_2D, textures[3]);
	ObjLoader artifactSphere("Objects\\artifact_sphere.obj");
	artifactSphere.create(-125, -35, -180);

	glDisable(GL_TEXTURE_2D);
	glPushMatrix();

	//calculating the rover's position
	//rover origin = (2, 0, -2.25)
	int rotationAxisOffset;
	glMatrixMode(GL_MODELVIEW);
	start_pos_x += cos(rotation_angle / radian) * velocity_L;
	start_pos_z += -sin(rotation_angle / radian) * velocity_L;
	glTranslatef(start_pos_x + 2, 0, start_pos_z - 2.25);
	glRotatef(rotation_angle, 0, 1, 0);
	glTranslatef(-start_pos_x - 2, 0, -start_pos_z + 2.25);
	glTranslatef(start_pos_x, 0, start_pos_z);
	//Cylinder c1;
	//c1.create(6, 2, 10, 0.1, 0, 0, 0.2);
	Rover rover1;
	rover1.create();
	glPopMatrix();
	glutSwapBuffers();
}


int main(int argc, char** argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 640);
	glutCreateWindow("Rover Sim");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	// here are the new entries
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(processKeyboardKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	//textures
	int width, height, nrChannels;
	unsigned char* data;
	glEnable(GL_TEXTURE_2D);
	glGenTextures(4, textures);

	//rock texture
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	data = stbi_load("Textures\\rock_texture.jpg", &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	//surface texture
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	data = stbi_load("Textures\\surface_texture.jpg", &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	//artifact rod texture
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	data = stbi_load("Textures\\artifact_rod_texture.jpg", &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	//artifact sphere texture
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	data = stbi_load("Textures\\artifact_sphere_texture.jpg", &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}