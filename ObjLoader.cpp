#include "ObjLoader.h"

ObjLoader::ObjLoader(std::string filenName)
{
	ifstream file(filenName);
	string str;
	GLfloat x, y, z;
	GLint a, b, c;
	char temp;
	int i = 0;
	while (getline(file,str))
	{
		if (str.substr(0, 1) == "v")
		{
			vector<GLfloat> point;
			istringstream inStr1(str.substr(2));
			inStr1 >> x;
			inStr1 >> y;
			inStr1 >> z;
			point.push_back(x);
			point.push_back(y);
			point.push_back(z);
			vertexCoordinates.push_back(point);

		}
		else if (str.substr(0, 1) == "f")
		{
			vector<GLint> Indexes;
			istringstream inStr2(str.substr(2));
			inStr2 >> a;
			inStr2 >> b;
			inStr2 >> c;
			Indexes.push_back(a - 1);
			Indexes.push_back(b - 1);
			Indexes.push_back(c - 1);
			vertexIndexes.push_back(Indexes);
		}
	}
	file.close();
}

void ObjLoader::create()
{
	vertex a, b, c;
	GLint vertexIndex1;
	GLint vertexIndex2;
	GLint vertexIndex3;
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < vertexIndexes.size(); i++)
	{
		vertexIndex1 = (vertexIndexes[i])[0];
		vertexIndex2 = (vertexIndexes[i])[1];
		vertexIndex3 = (vertexIndexes[i])[2];

		a.x = (vertexCoordinates[vertexIndex1])[0];
		a.y = (vertexCoordinates[vertexIndex1])[1];
		a.z = (vertexCoordinates[vertexIndex1])[2];

		b.x = (vertexCoordinates[vertexIndex2])[0];
		b.y = (vertexCoordinates[vertexIndex2])[1];
		b.z = (vertexCoordinates[vertexIndex2])[2];

		c.x = (vertexCoordinates[vertexIndex3])[0];
		c.y = (vertexCoordinates[vertexIndex3])[1];
		c.z = (vertexCoordinates[vertexIndex3])[2];

		glVertex3f(a.x, a.y, a.z);
		glVertex3f(b.x, b.y, b.z);
		glVertex3f(c.x, c.y, c.z);
	}
	glEnd();
}