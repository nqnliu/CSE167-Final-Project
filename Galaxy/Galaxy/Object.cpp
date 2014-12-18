#include "Object.h"

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include "main.h"
using namespace std;

Object::Object()
{
	model2world.identity();
}

Object::Object(char* filename)
{
	update(filename);
}

void Object::update(char* filename)
{
	model2world.identity();
	parser(filename);
	dataprocess();
}

void Object::parser(char* filename)
{
	FILE* fp;
	float x, y, z;
	float r, g, b;
	float nx, ny, nz;
	int vix, viy, viz;
	int nix, niy, niz;

	int c1, c2;
	int tmp;

	pts.clear();
	nml.clear();
	color.clear();
	ind.clear();

	fp = fopen(filename, "rb");
	if (fp == NULL) 
	{
		cerr << "error loading file" << filename << endl; 
		exit(-1);
	}

	while ( (c1 = fgetc(fp)) != EOF )
	{
		c2 = fgetc(fp);
		if (c1 == 'v' && c2 == ' ')
		{
//			fscanf(fp, "%f %f %f %f %f %f\n",
//				&x, &y, &z, &r, &g, &b);
			fscanf(fp, "%f %f %f\n", &x, &y, &z);
			pts.push_back( Vector3(x,y,z) );

			r = .2;
			g = .9;
			b = 1;
			color.push_back(Vector3(r, g, b));
		}
		if (c1 == 'v' && c2 == 'n')
		{
			fscanf(fp, "%f %f %f\n", &nx, &ny, &nz);
			nml.push_back(Vector3(nx,ny,nz));
		}
		if (c1 == 'f' && c2 == ' ')
		{
			fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&vix, &tmp, &nix, &viy, &tmp, &niy, &viz, &tmp, &niz);
			ind.push_back(make_pair(vix, nix));
			ind.push_back(make_pair(viy, niy));
			ind.push_back(make_pair(viz, niz));
		}
		if (c1 == '#' || (c1 == 'v' && c2 == 't'))
		{
			while ( (tmp = fgetc(fp)) != '\n' && (tmp != EOF));
		}
	}

	fclose(fp);
}

Object::~Object()
{
}

void Object::dataprocess()
{
	min.v[0] = max.v[0] = pts[0].v[0];
	for (int i = 0; i < pts.size(); ++i)
	{
		if (pts[i].v[0] < min.v[0])
		{
			min.v[0] = pts[i].v[0];
		}

		if (pts[i].v[0] > max.v[0])
		{
			max.v[0] = pts[i].v[0];
		}
	}

	min.v[1] = max.v[1] = pts[0].v[1];
	for (int i = 0; i < pts.size(); ++i)
	{
		if (pts[i].v[1] < min.v[1])
		{
			min.v[1] = pts[i].v[1];
		}

		if (pts[i].v[1] > max.v[1])
		{
			max.v[1] = pts[i].v[1];
		}
	}

	min.v[2] = max.v[2] = pts[0].v[2];
	for (int i = 0; i < pts.size(); ++i)
	{
		if (pts[i].v[2] < min.v[2])
		{
			min.v[2] = pts[i].v[2];
		}

		if (pts[i].v[2] > max.v[2])
		{
			max.v[2] = pts[i].v[2];
		}
	}

	min.print("min point coordinates:");
	max.print("max point coordinates:");


	model2world = model2world.makeTranslate(
		-(min.v[0] + max.v[0]) / 2,
		-(min.v[1] + max.v[1]) / 2,
		-(min.v[2] + max.v[2]) / 2
		);

	model2world.print("translate");

	Matrix4 scale;
	double s = 40 / (-min.v[0] + max.v[0]) +
		40 / (-min.v[1] + max.v[1]) +
		40 / (-min.v[2] + max.v[2]);
	s /= 3;
	scale = scale.makeScale(s, s, s);
	scale.print("scale");
	model2world = scale * model2world;

	model2world.print("t+s");

}

Matrix4& Object::getMatrix()
{
	return model2world;
}

Matrix4 Object::spin(double deg, int type)   // deg is in degrees
{
	Matrix4 rotate;
	if (type == 1)
		rotate = rotate.makeRotateX(deg);
	if (type == 2)
		rotate = rotate.makeRotateY(deg);
	if (type == 3)
		rotate = rotate.makeRotateZ(deg);
//	model2world = rotate * model2world;   // This creates the matrix to rotate the cube

	return rotate;
}

void Object::scale(double size)
{
	Matrix4 scale;
	scale = scale.makeScale(size, size, size);
	model2world = scale * model2world;
}


void Object::rotate(Vector3 axis, double angle)
{
	Matrix4 rotate;
	rotate = rotate.makeRotate(angle, axis);

	model2world = rotate * model2world;
}

void Object::translate(float tx, float ty, float tz)
{
	Matrix4 t;
	t = t.makeTranslate(tx, ty, tz);

	model2world = t * model2world;
}

void Object::render(Matrix4 M)
{
	glPushMatrix();

	Matrix4 newm = model2world * M *spin(-30, 3)* spin(-100, 1) * model2world.makeScale(1,1,4);
	newm.transpose();

	glLoadMatrixd(newm.getPointer());

	glBegin(GL_TRIANGLES);

	Vector3 tmp;
	int index;
	for (int i = 0; i < ind.size(); ++i)
	{
		index = ind[i].first;

		tmp = color[index - 1];
		glColor3f(tmp.v[0], tmp.v[1], tmp.v[2]);

		tmp = pts[index - 1];
		glVertex3f(tmp.v[0], tmp.v[1], tmp.v[2]);

		index = ind[i].second;

		tmp = nml[index - 1];
		tmp.normalize();
		glNormal3d(tmp.v[0], tmp.v[1], tmp.v[2]);
	}

	glEnd();

	glPopMatrix();
}