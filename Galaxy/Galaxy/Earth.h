#ifndef _EARTH_H_
#define _EARTH_H_
#include "Planet.h"
class Earth : public Planet
{
public:
   GLuint night_id;
   Earth(float, char *, char *, float);
   void setUpShader();
};

#endif