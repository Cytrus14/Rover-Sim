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
	void create();
private:
	vector<vector<GLfloat>> vertexCoordinates;
	vector<vector<GLint>> vertexIndexes;
	vector<vector<GLfloat>> textureCoordinates;
	vector<vector<GLint>> textureIndexes;
};
