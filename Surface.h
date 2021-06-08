#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <glut.h>

using namespace std;

class Surface
{
public:
	float Zmin;
	float Zmiddle;
	float Zmax;
	float minmax[3][2];
	float points[600][600];
	struct vertex
	{
		float x;
		float y;
		float z;
	};
	struct vt
	{
		float s;
		float t;
	};
	Surface(std::string fileName);
	void create(double offset_x = 0, double offset_y = 0, double offset_z = 0);
	void min2(float x1, float x2, float x3, float z1, float z2, float z3);
	void middle(float x1, float x2, float x3, float z1, float z2, float z3);
	void max2(float x1, float x2, float x3, float z1, float z2, float z3);
	void isInside(float x1, float x2, float x3, float z1, float z2, float z3, float y1, float y2, float y3);
private:
	vector<vector<GLfloat>> vertexCoordinates;
	vector<vector<GLint>> vertexIndexes;
	vector<vector<GLfloat>> textureCoordinates;
	vector<vector<GLint>> textureIndexes;
	bool isObjectCreated = false;
};
