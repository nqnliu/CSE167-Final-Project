#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <string>
using namespace std;

class Vector3
{
public:
	double v[3];    // vector elements;

public:
	Vector3();
	Vector3(double,double,double);
//	~Vector3();
	Vector3 operator+(const Vector3&);
	Vector3 operator-(const Vector3&);
	Vector3 negate();
	Vector3 scale(double s);
	double dot(const Vector3&);
	Vector3 cross(const Vector3&);
	double length();
	Vector3 normalize();
	void print(char[]);
};

#endif