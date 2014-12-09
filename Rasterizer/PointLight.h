#ifndef _POINTLIGHT_H_
#define _POINTLIGHT_H_

#include "Vector4.h"
#include "Vector3.h"

class PointLight
{
public:
   Vector3 position;
   Vector3 color;

   PointLight::PointLight(Vector3, Vector3);
   Vector3 calculateColor(Vector3, Vector3, Vector3);
};

#endif