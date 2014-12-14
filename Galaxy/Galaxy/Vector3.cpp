#include "Vector3.h"

//construction
Vector3::Vector3()
{
	for (int i = 0; i < 3; ++i)
	{
		v[i] = 0;
	}
}

Vector3::Vector3(double x,double y,double z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

//overload operator '+' for addition
Vector3 Vector3::operator+(const Vector3& v2)
{
	Vector3 res;
	res.v[0] = v[0] + v2.v[0];
	res.v[1] = v[1] + v2.v[1];
	res.v[2] = v[2] + v2.v[2];

	return res;
}

//overload operator '-' for substraction
Vector3 Vector3::operator-(const Vector3& v2)
{
	Vector3 res;
	res.v[0] = v[0] - v2.v[0];
	res.v[1] = v[1] - v2.v[1];
	res.v[2] = v[2] - v2.v[2];

	return res;
}

//negation
Vector3 Vector3::negate()
{
	Vector3 newv;

	newv = *this;
	newv.v[0] *= -1;
	newv.v[1] *= -1;
	newv.v[2] *= -1;
	return newv;
}

//scale (multiplication with scalar value)
Vector3 Vector3::scale(double s)
{
	Vector3 newv;

	newv = *this;
	newv.v[0] *= s;
	newv.v[1] *= s;
	newv.v[2] *= s;

	return newv;
}

//dot product, returns result
double Vector3::dot(const Vector3& v2)
{
	double res = 0;
	res += v[0] * v2.v[0];
	res += v[1] * v2.v[1];
	res += v[2] * v2.v[2];

	return res;
}

//cross product, returns result and puts it in calling vector
Vector3 Vector3::cross(const Vector3& v2)
{
	Vector3 res;
	res.v[0] = v[1] * v2.v[2] - v[2] * v2.v[1];
	res.v[1] = v[2] * v2.v[0] - v[0] * v2.v[2];
	res.v[2] = v[0] * v2.v[1] - v[1] * v2.v[0];

	return res;
}

//length of the vector
double Vector3::length()
{
	double res = 0;
	res += v[0] * v[0];
	res += v[1] * v[1];
	res += v[2] * v[2];
	res = sqrt(res);
	
	return res;
}

//normalize the vector (make it so that its length is equal to one)
Vector3 Vector3::normalize()
{
	double len = length();
	Vector3 newv;

	newv = *this;
	newv.v[0] /= len;
	newv.v[1] /= len;
	newv.v[2] /= len;
	return newv;
}

//print x, y and z components of the vector after a comment string
void Vector3::print(char comment[])
{
	printf("%s\n", comment);

	printf("[ %lf, %lf, %lf ]\n", v[0], v[1], v[2]);
	printf("\n");
}

