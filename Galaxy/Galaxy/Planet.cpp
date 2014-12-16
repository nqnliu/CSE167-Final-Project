#include "Planet.h"
#include "SOIL.h"
#include <stdlib.h>
#include <iostream>
#define NUM_DIVS 50
#define PI 3.14159
Planet::Planet(float size, char * texture, char * normal)
{
   //size = ((double)rand() / (RAND_MAX)) * 3 + 1;
   Planet::size = size;
   texture_file = texture;
   normal_file = normal;
}

void Planet::render()
{
   bumpMap->bind();
   glPushMatrix();
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, texture_id);
   glActiveTexture(GL_TEXTURE1);
   glBindTexture(GL_TEXTURE_2D, normal_id);
   glColor3f(color[0], color[1], color[2]);
   glRotatef(90, 1, 0, 0);
   glScalef(size, size, size);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);
   //glutSolidSphere(1.0, 50, 50);
   mySphere2();
   glPopMatrix();
   bumpMap->unbind();
}

void Planet::glow(float s)
{
//	lighting->bind();

	glPushMatrix();
	glColor4f(glowcolor[0], glowcolor[1], glowcolor[2], s);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glowcolor);
	glutSolidSphere(1.0, 50, 50);
	glPopMatrix();

//	lighting->unbind(); 
}

void Planet::renderGlow(float r, float g, float b)
{
	glowcolor[0] = r;
	glowcolor[1] = g;
	glowcolor[2] = b;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	float scaler;
	int n;
	float range;
	float step;

	range = 1.1;
	n = range * 40 - 40;
	step = .5 / n;

	for (int i = n; i >= 0; --i)
	{
		scaler = range - .026*(float)i;

		glPushMatrix();
		glScalef(scaler, scaler, scaler);
		glow(step);
		glPopMatrix();
	}

	glDisable(GL_BLEND);
}

void Planet::setUpShader()
{
   if (!bumpMap)
      bumpMap = new Shader("bump.vert", "bump.frag", true);

   bumpMap->bind();
   glActiveTexture(GL_TEXTURE0);
   texture_id = SOIL_load_OGL_texture
      (
      texture_file,
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_TEXTURE_REPEATS
      );
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glBindTexture(GL_TEXTURE_2D, texture_id);
   GLint uniformTex0 = glGetUniformLocation(bumpMap->pid, "colorMap");
   glUniform1i(uniformTex0, 0);

   glActiveTexture(GL_TEXTURE1);
   normal_id = SOIL_load_OGL_texture
      (
      normal_file,
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_TEXTURE_REPEATS
      );
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glBindTexture(GL_TEXTURE_2D, normal_id);
   uniformTex0 = glGetUniformLocation(bumpMap->pid, "normalMap");
   glUniform1i(uniformTex0, 1);
   bumpMap->unbind();

}

// Modified from the glu source code for gluSphere() for a multi-textured unit sphere with normals
void Planet::mySphere2()
{
   bumpMap->bind();
   GLint uniformTan = glGetAttribLocation(bumpMap->pid, "tangento");
   GLint i, j;
   GLfloat sintheta[NUM_DIVS + 1];
   GLfloat costheta[NUM_DIVS + 1];
   GLfloat sinphi[NUM_DIVS + 1];
   GLfloat cosphi[NUM_DIVS + 1];
   GLfloat angle;
   GLfloat sintemp1 = 0.0, sintemp2 = 0.0;
   GLfloat costemp1 = 0.0, costemp2 = 0.0;
   GLint slices = NUM_DIVS;
   GLint stacks = NUM_DIVS;
   GLfloat x, y, z;
   GLfloat s, t;
   GLfloat tangent[3];

   for (i = 0; i < slices; i++) {
      angle = 2.0 * PI * i / slices;
      sintheta[i] = sin(angle);
      costheta[i] = cos(angle);
   }

   for (j = 0; j <= stacks; j++) {
      angle = PI / 2.0 - PI * j / stacks;
      sinphi[j] = sin(angle);
      cosphi[j] = cos(angle);
   }
   /* Make sure it comes to a point */
   cosphi[0] = 0;
   cosphi[stacks] = 0;
   sintheta[slices] = sintheta[0];
   costheta[slices] = costheta[0];

   for (j = 0; j < stacks; j++) {
      sintemp1 = sinphi[j];
      sintemp2 = sinphi[j + 1];
      costemp1 = cosphi[j];
      costemp2 = cosphi[j + 1];

      glBegin(GL_QUAD_STRIP);
      for (i = 0; i <= slices; i++) {
         // Compute coordinates
         x = costheta[i] * costemp2;
         y = sintheta[i] * costemp2;
         z = sintemp2;
         s = 1 - (float)i / slices;
         t = 1 - (float)(j + 1) / stacks;
         tangent[0] = -costheta[i] * sintemp2;
         tangent[1] = -sintheta[i] * sintemp2;
         tangent[2] = costemp2;
         // Set vectors
         glNormal3f(x, y, z);
         glMultiTexCoord2f(GL_TEXTURE0, s, t);
         glMultiTexCoord2f(GL_TEXTURE1, s, t);
            // TODO: Set tangent vector in shader
         glVertexAttrib3f(uniformTan, tangent[0], tangent[1], tangent[2]);
         glVertex3f(x, y, z);

         // Compute coordinates
         x = costheta[i] * costemp1;
         y = sintheta[i] * costemp1;
         z = sintemp1;
         s = 1 - (float)i / slices;
         t = 1 - (float)j / stacks;
         tangent[0] = -costheta[i] * sintemp1;
         tangent[1] = -sintheta[i] * sintemp1;
         tangent[2] = costemp1;
         // Set vectors
         glNormal3f(x, y, z);
         glMultiTexCoord2f(GL_TEXTURE0, s, t);
         glMultiTexCoord2f(GL_TEXTURE1, s, t);
         glVertexAttrib3f(uniformTan, tangent[0], tangent[1], tangent[2]);
         // TODO: Set tangent vector in shader
         glVertex3f(x, y, z);
      }
      glEnd();
   }
   bumpMap->unbind();
}