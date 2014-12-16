#include "BezierCurve.h"
#include "main.h"

const float PI = 3.1415926535898;

// 3k+1 control points
BezierCurve::BezierCurve(int k)
{
	K = k;
	c_points = new Vector3[3*k+1];
	T = 0;
	status = 0;

	gen_points();
}

void BezierCurve::gen_points()
{
	c_points[0] = Vector3(0, 0, -20);
	c_points[1] = Vector3(20, 10, -20);
	c_points[2] = Vector3(20, 10, 20);
	c_points[3] = Vector3(0, 0, 20);
	c_points[4] = Vector3(-20, -10, 20);
	c_points[5] = Vector3(-20, -10, -20);
	c_points[6] = Vector3(0, 0, -20);
	printf("finish init\n");
}

BezierCurve::~BezierCurve()
{
	delete[]c_points;
}

Vector3 BezierCurve::bez
(float t, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3)
{
	Vector3 newv;
	Vector3 sig;
	Vector3 p[4] = { p0, p1, p2, p3 };
	float tmp;

	for (int i = 0; i < 4; ++i)
	{
		if (i == 0 || i == 3) tmp = 1;
		if (i == 1 || i == 2) tmp = 3;

		for (int j = 0; j < i; ++j)
		{
			tmp *= t;
		}

		for (int j = 0; j < 3 - i; ++j)
		{
			tmp *= 1 - t;
		}

		sig = p[i].scale(tmp);
		newv = newv + sig;
	}

	return newv;
}

Vector3 BezierCurve::getPosition (float t)
{
	if (t >= K)
	{
		t = t - ((int) t/K) * K;
	}

	int i;
	i = t;

	return bez(t-(float)i, c_points[i*3], c_points[i*3+1], c_points[i*3+2], c_points[i*3+3]);
}

void BezierCurve::move(float s)
{
	if (status == 0) return;
//	printf("new case:\n");

	T += s;
	if (T >= K) T -= K;

	Vector3 p, up;

	p = getPosition(T);
	up = Vector3(0,1,0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, double(window_width) / (double)window_height, 1.0, 1000.0); // set perspective projection viewing frustum
	gluLookAt(p.v[0], p.v[1], p.v[2], 5.0, 0, 0, up.v[0], up.v[1], up.v[2]);
	glMatrixMode(GL_MODELVIEW);
}

void BezierCurve::pause()
{
	status = 1 - status;
}