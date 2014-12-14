#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include <Windows.h>
#include "GLee.h"
#include <GL/glut.h>

class SkyBox
{
private:
	GLuint textures[6];

public:
   SkyBox::SkyBox();
   void render( float size = 100 );
   unsigned char* loadPPM(const char* filename, int& width, int& height);
   void loadTexture(GLuint texture, const char* filename);
   void createCubeMap();

};
#endif