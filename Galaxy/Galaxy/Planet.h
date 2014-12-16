#ifndef _PLANET_H
#define _PLANET_H

#include "shader.h"
#include <Windows.h>
#include "GLee.h"
#include <GL/glut.h>

class Planet
{
public:
	float glowcolor[3];
   float color[3];
   float size;
   Shader * bumpMap;
   GLuint texture_id;
   GLuint normal_id;
   char * texture_file;
   char * normal_file;

   Planet(float size, char * texture, char * normal);
   void render();
   void setUpShader();
   void mySphere2();
   void renderGlow(float, float, float);

private:
   void glow(float);
};
#endif