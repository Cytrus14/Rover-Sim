#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <glut.h>

using namespace std;

class ObjLoader 
{
public:
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
	ObjLoader(std::string fileName);
	void create(double offset_x = 0, double offset_y = 0, double offset_z = 0);
private:
	vector<vector<GLfloat>> vertexCoordinates;
	vector<vector<GLint>> vertexIndexes;
	vector<vector<GLfloat>> textureCoordinates;
	vector<vector<GLint>> textureIndexes;
	bool isObjectCreated = false;
};
