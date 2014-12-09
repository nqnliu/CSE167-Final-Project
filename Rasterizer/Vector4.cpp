#include <iostream>
#include <iomanip> 

#include "Vector4.h"

using namespace std;

Vector4::Vector4() : x(0.0), y(0.0), z(0.0), w(0.0)
{
}

Vector4::Vector4(double x0, double y0, double z0, double w0) : x(x0), y(y0), z(z0), w(w0)
{
}

Vector4 Vector4::operator+(const Vector4 &a)
{
   return Vector4(x + a.x, y + a.y, z + a.z, w);
}

Vector4 Vector4::operator-(const Vector4 &a)
{
   return Vector4(x - a.x, y - a.y, z - a.z, w);
}

double Vector4::length()
{
   return sqrt(x * x + y * y + z * z);
}

void Vector4::dehomogenize()
{
   // divide by 4th component
   if (w != 0.0)
   {
      x /= w;
      y /= w;
      z /= w;
      w = 1.0;
   }
}

void Vector4::print(string comment)
{
   cout << comment;
   cout << setprecision(2) << std::fixed << "(" << x << ", " << y << ", " << z << ", " << w << ")\n";
}