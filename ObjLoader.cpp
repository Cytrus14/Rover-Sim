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
		if (str.substr(0, 2) == "v ")
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
		else if (str.substr(0, 2) == "vt")
		{
			vector<GLfloat> point2D;
			istringstream inStr3((str.substr(3)));
			inStr3 >> x;
			inStr3 >> y;
			point2D.push_back(x);
			point2D.push_back(y);
			textureCoordinates.push_back(point2D);
		}
		//TODO: modify indexes reading method
		else if (str.substr(0, 1) == "f")
		{
			vector<GLint> verIndexes;
			vector<GLint> texIndexes;
			istringstream inStr2(str.substr(2));
			inStr2 >> a;
			inStr2 >> temp;
			inStr2 >> x;
			inStr2 >> b;
			inStr2 >> temp;
			inStr2 >> y;
			inStr2 >> c;
			inStr2 >> temp;
			inStr2 >> z;
			verIndexes.push_back(a - 1);
			verIndexes.push_back(b - 1);
			verIndexes.push_back(c - 1);
			texIndexes.push_back(x - 1);
			texIndexes.push_back(y - 1);
			texIndexes.push_back(z - 1);
			vertexIndexes.push_back(verIndexes);
			textureIndexes.push_back(texIndexes);
		}
	}
	file.close();
}

void ObjLoader::create()
{
	vertex a, b, c;
	vt x, y, z;
	GLint vertexIndex1;
	GLint vertexIndex2;
	GLint vertexIndex3;
	GLint textureIndex1;
	GLint textureIndex2;
	GLint textureIndex3;
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < vertexIndexes.size(); i++)
	{
		vertexIndex1 = (vertexIndexes[i])[0];
		vertexIndex2 = (vertexIndexes[i])[1];
		vertexIndex3 = (vertexIndexes[i])[2];
		textureIndex1 = (textureIndexes[i][0]);
		textureIndex2 = (textureIndexes[i][1]);
		textureIndex3 = (textureIndexes[i][2]);

		a.x = (vertexCoordinates[vertexIndex1])[0];
		a.y = (vertexCoordinates[vertexIndex1])[1];
		a.z = (vertexCoordinates[vertexIndex1])[2];

		b.x = (vertexCoordinates[vertexIndex2])[0];
		b.y = (vertexCoordinates[vertexIndex2])[1];
		b.z = (vertexCoordinates[vertexIndex2])[2];

		c.x = (vertexCoordinates[vertexIndex3])[0];
		c.y = (vertexCoordinates[vertexIndex3])[1];
		c.z = (vertexCoordinates[vertexIndex3])[2];

		x.s = (textureCoordinates[textureIndex1][0]);
		x.t = (textureCoordinates[textureIndex1][1]);

		y.s = (textureCoordinates[textureIndex2][0]);
		y.t = (textureCoordinates[textureIndex2][1]);

		z.s = (textureCoordinates[textureIndex3][0]);
		z.t = (textureCoordinates[textureIndex3][1]);

		glTexCoord2f(x.s, x.t);
		glVertex3f(a.x, a.y, a.z);
		glTexCoord2f(y.s, y.t);
		glVertex3f(b.x, b.y, b.z);
		glTexCoord2f(z.s, z.t);
		glVertex3f(c.x, c.y, c.z);
	}
	glEnd();
}