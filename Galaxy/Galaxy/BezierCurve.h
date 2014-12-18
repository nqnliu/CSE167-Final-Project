#ifndef _BEZIERCURVE_H
#define _BEZIERCURVE_H

#include "Vector3.h"

class BezierCurve
{
private:
	int K; // # of curves
	Vector3 *c_points;
	Vector3 *l_points;
	float T; //[0,K]
	int status;
	int width, height;

public:
	BezierCurve();
	~BezierCurve();
	Vector3 bez(float t, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3);
	void move(float);
	Vector3 getPosition(float t);
	Vector3 getLookAt(float t);
	void gen_points();
	void pause();
	void setwh(int,int);
};

#endif