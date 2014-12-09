#include <math.h>
#include <iostream>
#include <iomanip> 

#include "Vector3.h"

using namespace std;

Vector3::Vector3() : x(0.0), y(0.0), z(0.0)
{
}

Vector3::Vector3(double x0, double y0, double z0) : x(x0), y(y0), z(z0)
{
}

Vector3 Vector3::operator+(const Vector3 &a)
{
   return Vector3(x + a.x, y + a.y, z + a.z);
}

Vector3 Vector3::operator-(const Vector3 &a)
{
   return Vector3(x - a.x, y - a.y, z - a.z);
}

void Vector3::negate()
{
   x = -x;
   y = -y;
   z = -z;
}

void Vector3::scale(double s)
{
   x *= s;
   y *= s;
   z *= s;
}

double Vector3::dot(const Vector3 &a)
{
   return x * a.x + y * a.y + z * a.z;
}

Vector3 Vector3::cross(const Vector3 &a)
{
   double newX = y * a.z - z * a.y;
   double newY = z * a.x - x * a.z;
   double newZ = x * a.y - y * a.x;
   return Vector3(newX, newY, newZ);
}

double Vector3::length()
{
   return sqrt(x * x + y * y + z * z);
}

void Vector3::normalize()
{
   if (length() != 0.0)
   {
      scale(1.0 / length());
   }
}

void Vector3::print(string comment)
{
   cout << comment;
   //cout << setprecision(2) << std::fixed << "(" << x << ", " << y << ", " << z << ")\n";
   cout << std::fixed << "(" << x << ", " << y << ", " << z << ")\n";
}