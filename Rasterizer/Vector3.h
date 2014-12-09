#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <string>

class Vector3
{
public:
   double x, y, z;

   Vector3();
   Vector3(double, double, double);

   Vector3 operator+(const Vector3&);
   Vector3 operator-(const Vector3&);

   void negate();
   void scale(double);
   double dot(const Vector3&);
   Vector3 cross(const Vector3&);

   double length();
   void normalize();
   void print(std::string comment);
};

#endif