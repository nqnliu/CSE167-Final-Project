#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Matrix4.h"
#include <Vector>

class Object
{
public:
	vector<Vector3> pts;
	vector<Vector3> nml;
	vector<Vector3> color;
	vector<pair<int, int>> ind; //point & color, normal

	Vector3 min;
	Vector3 max;

	Matrix4 model2world;
public:
	Object();
	Object(char*);
	void parser(char* filename);
	void update(char* filename);
	~Object();
	Matrix4& getMatrix();
	Matrix4 spin(double, int);
	void scale(double);
	void dataprocess();
	void rotate(Vector3, double);
	void translate(float, float, float);

	void render(Matrix4);
};

#endif