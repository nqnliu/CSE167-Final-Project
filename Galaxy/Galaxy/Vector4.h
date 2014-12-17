#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include <string>

class Vector4
{
public:
   double x, y, z, w;

   Vector4::Vector4();
   Vector4::Vector4(double, double, double, double);

   Vector4 operator+(const Vector4 &a);
   Vector4 operator-(const Vector4 &a);
   Vector4 operator*(const Vector4 &a);
   Vector4 operator*(float);

   double length();

   float dot(const Vector4&);
   void scale(double);
   Vector4 cross(const Vector4&);
   void dehomogenize();
   void normalize();
   void print(std::string);
};

#endif