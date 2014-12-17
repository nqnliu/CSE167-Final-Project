#ifndef _PLANET_H
#define _PLANET_H

#include "shader.h"
#include "Geode.h"
#include <Windows.h>
#include "GLee.h"
#include <GL/glut.h>

class Planet : public Geode
{
public:
	float glowcolor[3];
   float color[3];
   float size;
   Shader * bumpMap;
   Shader * textureMap;
   GLuint texture_id;
   GLuint normal_id;
   char * texture_file;
   char * normal_file;
   bool bump;
   bool glowFlag;
   float orbit_velocity;

   Planet();
   Planet(float, char *, char *, float);
   void render();
   void setUpShader();
   void mySphere2();
   void renderGlow(float, float, float);
   void setGlow(float, float, float);
private:
   void glow(float);
};
#endif