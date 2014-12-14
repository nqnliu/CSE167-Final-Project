#include "SkyBox.h"
#include "main.h"
#include "SOIL.h"
#include <iostream>
using namespace std;

SkyBox::SkyBox()
{
}

void SkyBox::render( float size )
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDisable(GL_LIGHTING);

	glColor3f(1, 1, 1);
   glActiveTexture(GL_TEXTURE0);
	//front
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	
	glBegin(GL_QUADS);

	glNormal3f(0, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-size/2, -size/2, size/2);
	glTexCoord2f(1, 0);
	glVertex3f(-size/2, size/2, size/2);
	glTexCoord2f(0, 0);
	glVertex3f(size/2, size/2, size/2);
	glTexCoord2f(0, 1);
	glVertex3f(size / 2, -size / 2, size / 2);

	glEnd();
	
	//back
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glTexCoord2f(1, 1);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glTexCoord2f(1, 0);
	glVertex3f(size / 2, size / 2, -size / 2);
	glTexCoord2f(0, 0);
	glVertex3f(-size / 2, size / 2, -size / 2);

	glEnd();
	
	//left
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-size/2, size/2, size/2);
	glTexCoord2f(0, 1);
	glVertex3f(-size/2, -size/2, size/2);
	glTexCoord2f(1, 1);
	glVertex3f(-size/2, -size/2, -size/2);
	glTexCoord2f(1, 0);
	glVertex3f(-size/2, size/2, -size/2);

	glEnd();

	//right
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(size/2, -size/2, -size/2);
	glTexCoord2f(1, 1);
	glVertex3f(size/2, -size/2, size/2);
	glTexCoord2f(1, 0);
	glVertex3f(size/2, size/2, size/2);
	glTexCoord2f(0, 0);
	glVertex3f(size/2, size/2, -size/2);

	glEnd();
	
	//top
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(1, 0);
	glVertex3f(size/2, size/2, size/2);
	glTexCoord2f(0, 0);
	glVertex3f(-size/2, size/2, size/2);
	glTexCoord2f(0, 1);
	glVertex3f(-size/2, size/2, -size/2);
	glTexCoord2f(1, 1);
	glVertex3f(size/2, size/2, -size/2);

	glEnd();
	
	//bottom
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(1, 0);
	glVertex3f(size/2, -size/2, -size/2);
	glTexCoord2f(0, 0);
	glVertex3f(-size/2, -size/2, -size/2);
	glTexCoord2f(0, 1);
	glVertex3f(-size/2, -size/2, size/2);
	glTexCoord2f(1, 1);
	glVertex3f(size/2, -size/2, size/2);

	glEnd();

	glDisable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_TEXTURE_2D);
}

/** Load a ppm file from disk.
@input filename The location of the PPM file.  If the file is not found, an error message
will be printed and this function will return 0
@input width This will be modified to contain the width of the loaded image, or 0 if file not found
@input height This will be modified to contain the height of the loaded image, or 0 if file not found
@return Returns the RGB pixel data as interleaved unsigned chars (R0 G0 B0 R1 G1 B1 R2 G2 B2 .... etc) or 0 if an error ocured
*/
unsigned char* SkyBox::loadPPM(const char* filename, int& width, int& height)
{
   const int BUFSIZE = 128;
   FILE* fp;
   unsigned int read;
   unsigned char* rawData;
   char buf[3][BUFSIZE];
   char* retval_fgets;
   size_t retval_sscanf;

   if ((fp = fopen(filename, "rb")) == NULL)
   {
      std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
      width = 0;
      height = 0;
      return NULL;
   }

   // Read magic number:
   retval_fgets = fgets(buf[0], BUFSIZE, fp);

   // Read width and height:
   do
   {
      retval_fgets = fgets(buf[0], BUFSIZE, fp);
   } while (buf[0][0] == '#');
   retval_sscanf = sscanf(buf[0], "%s %s", buf[1], buf[2]);
   width = atoi(buf[1]);
   height = atoi(buf[2]);

   // Read maxval:
   do
   {
      retval_fgets = fgets(buf[0], BUFSIZE, fp);
   } while (buf[0][0] == '#');

   // Read image data:
   rawData = new unsigned char[width * height * 3];
   read = fread(rawData, width * height * 3, 1, fp);
   fclose(fp);
   if (read != 1)
   {
      std::cerr << "error parsing ppm file, incomplete data" << std::endl;
      delete[] rawData;
      width = 0;
      height = 0;
      return NULL;
   }

   return rawData;
}


// load image file into texture object
void SkyBox::loadTexture(GLuint texture, const char* filename)
{
	int twidth, theight;   // texture width/height [pixels]
	unsigned char* tdata;  // texture pixel data

	// Load image file
	tdata = loadPPM(filename, twidth, theight);
	if (tdata == NULL) return;

	// Set this texture to be the one we are working with
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);

}

void SkyBox::createCubeMap()
{
	glEnable(GL_TEXTURE_2D);
   glActiveTexture(GL_TEXTURE0);

	loadTexture(textures[0], "right.ppm");
	loadTexture(textures[1], "left.ppm");
	loadTexture(textures[2], "bottom.ppm");
	loadTexture(textures[3], "top.ppm");
	loadTexture(textures[4], "front.ppm");
	loadTexture(textures[5], "back.ppm");

	glDisable(GL_TEXTURE_2D);
}