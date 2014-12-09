#include "PointLight.h"
#include <iostream>
#include <algorithm>

#define M_PI 3.14159265358979323846

PointLight::PointLight(Vector3 position, Vector3 color)
{
   PointLight::position = position;
   PointLight::color = color;
}

Vector3 PointLight::calculateColor(Vector3 pointPos, Vector3 pointNormal, Vector3 pointColor)
{
   Vector3 Ld = position - pointPos;
   double distance = Ld.length();
   Ld.normalize();
   pointNormal.normalize();
   //Ld.print("Ld = ");
   //std::cout << "distance = " << distance << "\n";
   Vector3 Li = Vector3(color.x, color.y, color.z);
   Li.scale(200);
   Li.scale(1.0 / (distance * distance));
   //Lc.print("Lc = ");

   double lDotNorm = Ld.dot(pointNormal);
   lDotNorm = std::max(lDotNorm, 0.05);
   //std::cout << "lDotNorm = " << lDotNorm << "\n";
   double oneOverPi = 1.0;                                                          

   double newR = oneOverPi * pointColor.x * Li.x * lDotNorm;
   double newG = oneOverPi * pointColor.y * Li.y * lDotNorm;
   double newB = oneOverPi * pointColor.z * Li.z * lDotNorm;

   Vector3 newColor = Vector3(newR, newG, newB);

   return newColor;
}