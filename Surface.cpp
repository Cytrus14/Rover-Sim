#include "Surface.h"

Surface::Surface(std::string filenName)
{
	ifstream file(filenName);
	string str;
	GLfloat x, y, z;
	GLint a, b, c;
	char temp;
	while (getline(file, str))
	{
		//odczytywanie koordynatow wierzcholkow
		if (str.substr(0, 2) == "v ")
		{
			vector<GLfloat> point; //wektor zapisujacy koordynaty danego wierzcholka
			istringstream inStr1(str.substr(2)); //kordynaty zaczynaja sie od drugiego znaku danej lini
			inStr1 >> x;
			inStr1 >> y;
			inStr1 >> z;
			//umieszczenie odczytanych wspolzednych w wektorze
			point.push_back(x);
			point.push_back(y);
			point.push_back(z);
			//umieszczenie wektora point w wektorze vertexCoordinates
			vertexCoordinates.push_back(point);
		}
		//odczytywanie wspolrzednych tekstur
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
		//odczytywanie indeksow wierzcholkow i tekstur
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
			//pomniejszanie odczytanych indeksow o 1 (w plikach indeksowanie zaczyna sie od 1, a nie od 0)
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

void Surface::create(double offset_x, double offset_y, double offset_z)
{
	if (!isObjectCreated)
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

			glTexCoord2f(x.s + offset_x, x.t + offset_y);
			glVertex3f(a.x + offset_x, a.y + offset_y, a.z + offset_z);
			glTexCoord2f(y.s + offset_x, y.t + offset_y);
			glVertex3f(b.x + offset_x, b.y + offset_y, b.z + offset_z);
			glTexCoord2f(z.s + offset_x, z.t + offset_y);
			glVertex3f(c.x + offset_x, c.y + offset_y, c.z + offset_z);

			isInside(a.x, b.x, c.x, a.z, b.z, c.z, a.y, b.y, c.y);
		}
		glEnd();
	}
}
void Surface::min2(float x1, float x2, float x3, float z1, float z2, float z3)
{
	if (x1 <= x2 && x1 <= x3)
	{
		minmax[0][0] = x1;
		minmax[0][1] = z1;
	}
	else if (x2 <= x1 && x2 <= x3)
	{
		minmax[0][0] = x2;
		minmax[0][1] = z2;
	}
	else
	{
		minmax[0][0] = x3;
		minmax[0][1] = z3;
	}
}

void Surface::middle(float x1, float x2, float x3, float z1, float z2, float z3)
{
	if (x1 >= x2 && x1 <= x3)
	{
		minmax[1][0] = x1;
		minmax[1][1] = z1;
	}
	else if (x1 <= x2 && x1 >= x3)
	{
		minmax[1][0] = x1;
		minmax[1][1] = z1;
	}
	else if (x2 >= x1 && x2 <= x3)
	{
		minmax[1][0] = x2;
		minmax[1][1] = z2;
	}
	else if (x2 <= x1 && x2 >= x3)
	{
		minmax[1][0] = x2;
		minmax[1][1] = z2;
	}
	else
	{
		minmax[1][0] = x3;
		minmax[1][1] = z3;
	}
}


void Surface::max2(float x1, float x2, float x3, float z1, float z2, float z3)
{
	if (x1 >= x2 && x1 >= x3)
	{
		minmax[2][0] = x1;
		minmax[2][1] = z1;
	}
	else if (x2 >= x1 && x2 >= x3)
	{
		minmax[2][0] = x2;
		minmax[2][1] = z2;
	}
	else
	{
		minmax[2][0] = x3;
		minmax[2][1] = z3;
	}
}

void Surface::isInside(float x1, float x2, float x3, float z1, float z2, float z3, float y1, float y2, float y3)
{
	min2(x1, x2, x3, z1, z2, z3);
	middle(x1, x2, x3, z1, z2, z3);
	max2(x1, x2, x3, z1, z2, z3);
	Zmiddle = ((minmax[0][1] - minmax[2][1]) / (minmax[0][0] - minmax[2][0])) * minmax[1][0] + minmax[0][1] - ((minmax[0][1] - minmax[2][1]) / (minmax[0][0] - minmax[2][0])) * minmax[0][0];

	if (Zmiddle < minmax[1][1])
	{
		for (int i = minmax[0][0]; i <= minmax[1][0]; i++)
		{
			Zmin = ((minmax[0][1] - minmax[2][1]) / (minmax[0][0] - minmax[2][0])) * i + minmax[0][1] - ((minmax[0][1] - minmax[2][1]) / (minmax[0][0] - minmax[2][0])) * minmax[0][0];
			Zmax = ((minmax[0][1] - minmax[1][1]) / (minmax[0][0] - minmax[1][0])) * i + minmax[0][1] - ((minmax[0][1] - minmax[1][1]) / (minmax[0][0] - minmax[1][0])) * minmax[0][0];
			for (int j = Zmin; j <= Zmax; j++)
			{
				float det = (z2 - z3) * (x1 - x3) + (x3 - x2) * (z1 - z3);
				float l1 = ((z2 - z3) * (i - x3) + (x3 - x2) * (j - z3)) / det;
				float l2 = ((z3 - z1) * (i - x3) + (x1 - x3) * (j - z3)) / det;
				float l3 = 1.0f - l1 - l2;
				points[i + 300][j + 300] = l1 * y1 + l2 * y2 + l3 * y3;
			}
		}
		for (int i = minmax[1][0] + 1; i <= minmax[2][0]; i++)
		{
			Zmin = ((minmax[0][1] - minmax[2][1]) / (minmax[0][0] - minmax[2][0])) * i + minmax[0][1] - ((minmax[0][1] - minmax[2][1]) / (minmax[0][0] - minmax[2][0])) * minmax[0][0];
			Zmax = ((minmax[1][1] - minmax[2][1]) / (minmax[1][0] - minmax[2][0])) * i + minmax[1][1] - ((minmax[1][1] - minmax[2][1]) / (minmax[1][0] - minmax[2][0])) * minmax[1][0];
			for (int j = Zmin; j <= Zmax; j++)
			{
				float det = (z2 - z3) * (x1 - x3) + (x3 - x2) * (z1 - z3);
				float l1 = ((z2 - z3) * (i - x3) + (x3 - x2) * (j - z3)) / det;
				float l2 = ((z3 - z1) * (i - x3) + (x1 - x3) * (j - z3)) / det;
				float l3 = 1.0f - l1 - l2;
				points[i + 300][j + 300] = l1 * y1 + l2 * y2 + l3 * y3;
			}
		}
	}
	else if (Zmiddle == minmax[1][1] || (Zmiddle - minmax[1][1]) < 0.0001 || (Zmiddle - minmax[1][1]) > 0.0001)
	{
		minmax[1][0] += 0.01;
		for (int i = minmax[0][0]; i <= minmax[1][0]; i++)
		{
			Zmax = ((minmax[0][1] - minmax[2][1]) / (minmax[0][0] - minmax[2][0])) * i + minmax[0][1] - ((minmax[0][1] - minmax[2][1]) / (minmax[0][0] - minmax[2][0])) * minmax[0][0];
			Zmin = ((minmax[0][1] - minmax[1][1]) / (minmax[0][0] - minmax[1][0])) * i + minmax[0][1] - ((minmax[0][1] - minmax[1][1]) / (minmax[0][0] - minmax[1][0])) * minmax[0][0];
			for (int j = Zmin; j <= Zmax; j++)
			{
				float det = (z2 - z3) * (x1 - x3) + (x3 - x2) * (z1 - z3);
				float l1 = ((z2 - z3) * (i - x3) + (x3 - x2) * (j - z3)) / det;
				float l2 = ((z3 - z1) * (i - x3) + (x1 - x3) * (j - z3)) / det;
				float l3 = 1.0f - l1 - l2;
				points[i + 300][j + 300] = l1 * y1 + l2 * y2 + l3 * y3;
			}
		}
		for (int i = minmax[1][0] + 1; i <= minmax[2][0]; i++)
		{
			Zmax = ((minmax[0][1] - minmax[2][1]) / (minmax[0][0] - minmax[2][0])) * i + minmax[0][1] - ((minmax[0][1] - minmax[2][1]) / (minmax[0][0] - minmax[2][0])) * minmax[0][0];
			Zmin = ((minmax[1][1] - minmax[2][1]) / (minmax[1][0] - minmax[2][0])) * i + minmax[1][1] - ((minmax[1][1] - minmax[2][1]) / (minmax[1][0] - minmax[2][0])) * minmax[1][0];
			for (int j = Zmin; j <= Zmax; j++)
			{
				float det = (z2 - z3) * (x1 - x3) + (x3 - x2) * (z1 - z3);
				float l1 = ((z2 - z3) * (i - x3) + (x3 - x2) * (j - z3)) / det;
				float l2 = ((z3 - z1) * (i - x3) + (x1 - x3) * (j - z3)) / det;
				float l3 = 1.0f - l1 - l2;
				points[i + 300][j + 300] = l1 * y1 + l2 * y2 + l3 * y3;
			}
		}
	}
	else
	{
		for (int i = minmax[0][0]; i <= minmax[1][0]; i++)
		{
			Zmax = ((minmax[0][1] - minmax[2][1]) / (minmax[0][0] - minmax[2][0])) * i + minmax[0][1] - ((minmax[0][1] - minmax[2][1]) / (minmax[0][0] - minmax[2][0])) * minmax[0][0];
			Zmin = ((minmax[0][1] - minmax[1][1]) / (minmax[0][0] - minmax[1][0])) * i + minmax[0][1] - ((minmax[0][1] - minmax[1][1]) / (minmax[0][0] - minmax[1][0])) * minmax[0][0];
			for (int j = Zmin; j <= Zmax; j++)
			{
				float det = (z2 - z3) * (x1 - x3) + (x3 - x2) * (z1 - z3);
				float l1 = ((z2 - z3) * (i - x3) + (x3 - x2) * (j - z3)) / det;
				float l2 = ((z3 - z1) * (i - x3) + (x1 - x3) * (j - z3)) / det;
				float l3 = 1.0f - l1 - l2;
				points[i + 300][j + 300] = l1 * y1 + l2 * y2 + l3 * y3;
			}
		}
		for (int i = minmax[1][0] + 1; i <= minmax[2][0]; i++)
		{
			Zmax = ((minmax[0][1] - minmax[2][1]) / (minmax[0][0] - minmax[2][0])) * i + minmax[0][1] - ((minmax[0][1] - minmax[2][1]) / (minmax[0][0] - minmax[2][0])) * minmax[0][0];
			Zmin = ((minmax[1][1] - minmax[2][1]) / (minmax[1][0] - minmax[2][0])) * i + minmax[1][1] - ((minmax[1][1] - minmax[2][1]) / (minmax[1][0] - minmax[2][0])) * minmax[1][0];
			for (int j = Zmin; j <= Zmax; j++)
			{
				float det = (z2 - z3) * (x1 - x3) + (x3 - x2) * (z1 - z3);
				float l1 = ((z2 - z3) * (i - x3) + (x3 - x2) * (j - z3)) / det;
				float l2 = ((z3 - z1) * (i - x3) + (x1 - x3) * (j - z3)) / det;
				float l3 = 1.0f - l1 - l2;
				points[i + 300][j + 300] = l1 * y1 + l2 * y2 + l3 * y3;
			}
		}
	}
}