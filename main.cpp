#define radian 57.29578
#include <Windows.h>
#include <math.h>
#include "Rover.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "ObjLoader.h"
#include "Surface.h"

// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f, ly = 0.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f, y = 0.0f;

float red, green, blue;

unsigned int textures[4];

//rover's x and y coordinates
float rover_pos_x = 0;
float rover_pos_z = 0;
float rover_pos_y = 0;

//rover's rotation variables
float wheels_angle = 0.0;
float rover_angle = 0.0;
float rotation_radius = 0.0;

//rover velocities
float velocity = 0.0;
float angular_velocity = 0.0;

//loading objects
ObjLoader rock1("Objects\\rock.obj");
ObjLoader rock2("Objects\\rock.obj");
ObjLoader rock3("Objects\\rock.obj");
ObjLoader rock4("Objects\\rock.obj");
ObjLoader rock5("Objects\\rock.obj");
Surface terrain("Objects\\surface_test.obj");
ObjLoader artifactBase("Objects\\artifact_base.obj");
ObjLoader artifactRods("Objects\\artifact_rods.obj");
ObjLoader artifactSphere("Objects\\artifact_sphere.obj");

//colision points
float front[] = { -2.5, -0.9, -2.25 };
float back[] = { 3.5,-0.9,-2.25 };

//collision function
bool collisionDetection()
{
	front[0] += cos(rover_angle) * velocity;
	back[0] += cos(rover_angle) * velocity;
	front[2] += -sin(rover_angle) * velocity;
	back[2] += -sin(rover_angle) * velocity;
	if (terrain.points[int(front[0]) + 300][int(front[2]) + 300] >= 99)
		return 0;
	if (terrain.points[int(back[0]) + 300][int(back[2]) + 300] >= 99)
		return 0;
	return 1;
}

bool isColiding;

void timerCallback(int value)
{
	glutTimerFunc(50, timerCallback, 0);
	velocity = 0.97 * velocity;
}


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

	float fraction = 3.0f;

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
		if(velocity > -0.5)
			velocity -= 0.02;
		break;
	case 's':
		if (velocity < 0.5)
			velocity += 0.02;
		break;
	case 'd':
		if(wheels_angle > -40)
			wheels_angle -= 3.0;
		break;
	case 'a':
		if(wheels_angle < 40)
			wheels_angle += 3.0;
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
	glColor3f(0.8, 0.8, 0.8);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	rock1.create(0,-29,25);
	rock2.create(30,-19,-50);
	rock3.create(-40,-42,-83);
	rock4.create(20,-17,9);
	rock5.create(-69, -50, 19);
	Cylinder c1;

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	terrain.create(0,0,0);
	//generating invisible walls
	for (int i = -150; i <= -100; i++)
		for (int j = -200; j <= -151; j++)
			terrain.points[i + 300][j + 300] = 100;
	for(int i = 0; i < 7; i++)
		for (int j = 21; j <= 28; j++)
			terrain.points[i + 300][j + 300] = 100;
	for (int i = 30; i < 37; i++)
		for (int j = -53; j <= -46; j++)
			terrain.points[i + 300][j + 300] = 100;
	for (int i = 30; i < 37; i++)
		for (int j = -53; j <= -46; j++)
			terrain.points[i + 300][j + 300] = 100;
	for (int i = -40; i < -33; i++)
		for (int j = -86; j <= -79; j++)
			terrain.points[i + 300][j + 300] = 100;
	for (int i = 23; i < 30; i++)
		for (int j = 9; j <= 16; j++)
			terrain.points[i + 300][j + 300] = 100;
	for (int i = -67; i < -64; i++)
		for (int j = 20; j <= 27; j++)
			terrain.points[i + 300][j + 300] = 100;

	//for (int i = 0; i <= 600; i++)
	//{
	//	for (int j = 0; j <= 600; j++)
	//	{
	//		glColor3f(0.0, 1.0, 0.0);
	//		glBegin(GL_POINTS);
	//		glVertex3f(i - 300, terrain.points[i][j], j - 300);
	//		glEnd();
	//	}
	//}

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	artifactBase.create(-125,-35,-180);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	artifactRods.create(-125, -35, -180);

	glBindTexture(GL_TEXTURE_2D, textures[3]);
	artifactSphere.create(-125,-35, -180);

	glDisable(GL_TEXTURE_2D);
	
	glPushMatrix();
	//calculating the rover's position
	//rover origin = (2, 0, -2.25)
	isColiding = collisionDetection();
	std::cout << isColiding << '\n';
	if (terrain.points[int(front[0]) + 300][int(front[2]) + 300] < front[1] && terrain.points[int(back[0]) + 300][int(back[2]) + 300] < back[1])
	{
		front[1] = terrain.points[int(front[0]) + 300][int(front[2]) + 300];
		back[1] = terrain.points[int(back[0]) + 300][int(back[2]) + 300];

		rover_pos_y = terrain.points[int(back[0]) + 300][int(back[2]) + 300];
	}
	else if (terrain.points[int(front[0]) + 300][int(front[2]) + 300] > front[1] && terrain.points[int(back[0]) + 300][int(back[2]) + 300] > back[1])
	{
		if (terrain.points[int(back[0]) + 300][int(back[2]) + 300] - front[1] < 6)
		{
			front[1] = terrain.points[int(back[0]) + 300][int(back[2]) + 300];
			back[1] = terrain.points[int(back[0]) + 300][int(back[2]) + 300];
			rover_pos_y = terrain.points[int(back[0]) + 300][int(back[2]) + 300];
		}
	}
	glMatrixMode(GL_MODELVIEW);
	if (isColiding)
	{
		if (wheels_angle != 0)
		{
			rotation_radius = 1.9 / tan(wheels_angle / radian);
			angular_velocity = -velocity / rotation_radius;
		}
		else
		{
			rotation_radius = 0;
			angular_velocity = 0;
		}
		rover_angle += angular_velocity;
		rover_pos_x += cos(rover_angle) * velocity;
		rover_pos_z += -sin(rover_angle) * velocity;
		glTranslatef(rover_pos_x + 3.2, 0, rover_pos_z - 2);
		glRotatef(rover_angle * radian, 0, 1, 0);
		glTranslatef(-rover_pos_x - 3.2, 0, -rover_pos_z + 2);
		glTranslatef(rover_pos_x, rover_pos_y, rover_pos_z);
	}
	else
	{
		velocity = 0;
		if (wheels_angle != 0)
		{
			rotation_radius = 1.9 / tan(wheels_angle / radian);
			angular_velocity = -velocity / rotation_radius;
		}
		else
		{
			rotation_radius = 0;
			angular_velocity = 0;
		}
		rover_angle += angular_velocity;
		rover_pos_x += cos(rover_angle) * velocity;
		rover_pos_z += -sin(rover_angle) * velocity;
		glTranslatef(rover_pos_x + 3.2, 0, rover_pos_z - 2);
		glRotatef(rover_angle * radian, 0, 1, 0);
		glTranslatef(-rover_pos_x - 3.2, 0, -rover_pos_z + 2);
		glTranslatef(rover_pos_x, rover_pos_y, rover_pos_z);
	}
	Rover rover1;
	rover1.create(wheels_angle);
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
	//configuring timer
	glutTimerFunc(50, timerCallback, 0);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}