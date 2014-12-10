#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "GL\glut.h"

class SkyBox
{
public:
   SkyBox::SkyBox();
   void render();
   unsigned char* loadPPM(const char* filename, int& width, int& height);
   GLuint loadTexture(char * ppmFile, GLenum side_target);
   void createCubeMap();

};
#endif