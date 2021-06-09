#define radian 57.29578
#include <Windows.h>
#include <math.h>
#include "Rover.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "ObjLoader.h"
#include "Surface.h"
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>

//setting up rng
std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator
std::uniform_int_distribution<> distr(100, 500); // define the range

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
ObjLoader collectible1("Objects\\collectible.obj");
ObjLoader collectible2("Objects\\collectible.obj");
ObjLoader collectible3("Objects\\collectible.obj");

//collisions
//colision points
float front[] = { -2.5, -0.9, -2.25 };
float back[] = { 3.5,-0.9,-2.25 };

bool isColiding;

//collectibles
struct pos
{
	int x;
	int y;
	int z;
};
vector<pos> collectiblePositions;
vector<ObjLoader> collectibles;
int collectibleCount = 3;
int gatheredCollectibles = 0;
float collectibleRotation = 0;
bool* isCollectibleCollected;
std::chrono::time_point<std::chrono::system_clock> start, finish;
bool firstSimRun = true;

//score
vector<double> bestScores;
vector<string> scoreStrings;

//difficulty
bool wasDifficultyChanged = false;

//other strings
string ringsToCollectText = "Collected Rings:";
string bestTimes = "Best Times:";
string tempString;

void processMenuEvents(int value)
{
	switch (value)
	{
	case 1:
		collectibleCount = 3;
		break;
	case 2:
		collectibleCount = 5;
		break;
	case 3:
		collectibleCount = 10;
		break;
	}
	wasDifficultyChanged = true;
}
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


void timerCallback(int value)
{
	glutTimerFunc(50, timerCallback, 0);
	velocity = 0.97 * velocity;
	collectibleRotation += 10;
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

void setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0); //############

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void renderSpacedBitmapString(

	float x,
	float y,
	void* font,
	string str) {

	char* c;
	char* charStr = new char[str.length() + 1];
	int x1 = x;
	int i = 0;
	for (; i < str.length(); i++)
	{
		charStr[i] = str.at(i);
	}
	charStr[i] = '\0';

	for (c = charStr; *c != '\0'; c++) {

		glRasterPos2f(x1, y);
		glutBitmapCharacter(font, *c);
		x1 = x1 + glutBitmapWidth(font, *c);
	}
	delete[] charStr;
}

void resetSim()
{
	finish = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_time = finish - start;
	rover_pos_x = 0;
	rover_pos_z = 0;
	rover_angle = 0;
	velocity = 0;
	front[0] = -2.5;
	front[1] = -0.9;
	front[2] = -2.25;
	back[0] = 3.5;
	back[1] = -0.9;
	back[2] = -2.25;

	//adding time to score board
	int i = 0;
	if (!firstSimRun && !wasDifficultyChanged)
	{
		delete[] isCollectibleCollected;
		bestScores.push_back(elapsed_time.count());
		std::sort(bestScores.begin(), bestScores.end());
		int temp;
		if (bestScores.size() <= 3)
			temp = bestScores.size();
		else
			temp = 3;
		while (i < temp)
		{
			scoreStrings.at(i) = (to_string(bestScores.at(i)));
			if (i > 2)
				break;
			i++;
		}
	}
	isCollectibleCollected = new bool[collectibleCount];
	//reseting the clock
	start = std::chrono::system_clock::now();
	//handling collectibles
	collectiblePositions.clear();
	collectibles.clear();
	//generating new collectible positions
	pos collectibleTempPos;
	for (i = 0; i < collectibleCount; i++)
	{
		collectibleTempPos.x = distr(gen);
		collectibleTempPos.z = distr(gen);
		if (terrain.points[collectibleTempPos.x][collectibleTempPos.z] < 80 && terrain.points[collectibleTempPos.x][collectibleTempPos.z]!=0)
		{
			collectibleTempPos.y = terrain.points[collectibleTempPos.x][collectibleTempPos.z];
			collectibleTempPos.x -= 300;
			collectibleTempPos.z -= 300;
			collectiblePositions.push_back(collectibleTempPos);
		}
		else
		{
			i--;
		}
	}

	ObjLoader tempCollectible("Objects\\collectible.obj");
	for (i = 0; i < collectibleCount; i++)
	{
		collectibles.push_back(tempCollectible);
		isCollectibleCollected[i] = false;

	}
	std::cout << collectibleCount << "\n";
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

	glMatrixMode(GL_MODELVIEW);


	//if (!isCollectibleCollected[0])
	//{
	//	glPushMatrix();
	//	glTranslatef(-60, -45, -25);
	//	glRotatef(collectibleRotation, 0, 1, 0);
	//	glTranslatef(60, 45, 25);
	//	collectible1.create(-60, -45, -25);
	//	glPopMatrix();
	//}
	//if (!isCollectibleCollected[1])
	//{
	//	glPushMatrix();
	//	glTranslatef(-100, -55, 90);
	//	glRotatef(collectibleRotation, 0, 1, 0);
	//	glTranslatef(100, 55, -90);
	//	collectible2.create(-100, -55, 90);
	//	glPopMatrix();
	//}

	//if (!isCollectibleCollected[2])
	//{
	//	glPushMatrix();
	//	glTranslatef(-130, -55, -110);
	//	glRotatef(collectibleRotation, 0, 1, 0);
	//	glTranslatef(130, 55, 110);
	//	collectible3.create(-130, -50, -110);
	//	glPopMatrix();
	//}

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

	//handling collectibles
	//if (abs(rover_pos_x + 60) < 7 && abs(rover_pos_z + 25) < 7)
	//	isCollectibleCollected[0] = true;
	//if (abs(rover_pos_x + 100) < 7 && abs(rover_pos_z - 55) < 7)
	//	isCollectibleCollected[1] = true;
	//if (abs(rover_pos_x + 130) < 7 && abs(rover_pos_z + 110) < 7)
	//	isCollectibleCollected[2] = true;

	if (gatheredCollectibles == collectibleCount || firstSimRun || wasDifficultyChanged)
	{
		resetSim();
		firstSimRun = false;
		wasDifficultyChanged = false;
	}
	glDisable(GL_TEXTURE_2D);
	glColor3f(1, 0.84, 0.0);
	for (int i = 0; i < collectibleCount; i++)
	{
		if (!isCollectibleCollected[i])
		{
			glPushMatrix();
			glTranslatef(collectiblePositions.at(i).x, collectiblePositions.at(i).y + 4, collectiblePositions.at(i).z);
			glRotatef(collectibleRotation, 0, 1, 0);
			glTranslatef(-collectiblePositions.at(i).x, -(collectiblePositions.at(i).y + 4), -collectiblePositions.at(i).z);
			collectibles.at(i).create(collectiblePositions.at(i).x, collectiblePositions.at(i).y + 4, collectiblePositions.at(i).z);
			glPopMatrix();
		}
	}

	gatheredCollectibles = 0;
	for (int i = 0; i < collectibleCount; i++)
	{
		if (abs((collectiblePositions.at(i).x) - (rover_pos_x)) < 7 && abs((collectiblePositions.at(i).z) -(rover_pos_z)) < 7)
			isCollectibleCollected[i] = true;
		if (isCollectibleCollected[i])
			gatheredCollectibles++;
	}
	glEnable(GL_TEXTURE_2D);
	glColor3f(0.8, 0.8, 0.8);
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

	//displaying text
	int y = 15;
	short int temp;
	if (bestScores.size() <= 3)
		temp = bestScores.size();
	else
		temp = 3;
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	tempString = to_string(gatheredCollectibles);
	renderSpacedBitmapString(3, y, GLUT_BITMAP_8_BY_13, ringsToCollectText);
	renderSpacedBitmapString(135, y, GLUT_BITMAP_8_BY_13, tempString);
	tempString = "/";
	renderSpacedBitmapString(145, y, GLUT_BITMAP_8_BY_13, tempString);
	tempString = to_string(collectibleCount);
	renderSpacedBitmapString(155, y, GLUT_BITMAP_8_BY_13, tempString);
	y += 25;
	renderSpacedBitmapString(3, y, GLUT_BITMAP_8_BY_13, bestTimes);
	for (int i = 0; i < temp; i++)
	{
		y += 15;
		tempString = scoreStrings.at(i);
		if(tempString.length() > 0)
			tempString.append(" s");
		renderSpacedBitmapString(3, y, GLUT_BITMAP_8_BY_13, tempString);
		tempString.clear();
	}
	glPopMatrix();

	restorePerspectiveProjection();
	glutSwapBuffers();
}


int main(int argc, char** argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1600,900);
	glutCreateWindow("Rover Sim");

	//creating menu
	int menu;
	menu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Easy", 1);
	glutAddMenuEntry("Medium", 2);
	glutAddMenuEntry("Hard", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

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
	scoreStrings.push_back("");
	scoreStrings.push_back("");
	scoreStrings.push_back("");
	start = std::chrono::system_clock::now();
	glutMainLoop();

	return 1;
}