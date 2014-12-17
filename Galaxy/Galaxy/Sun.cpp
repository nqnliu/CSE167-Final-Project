#include "Sun.h"
#include <Windows.h>
#include "GLee.h"

Sun::Sun() : Planet(109, "Textures/sunmap.jpg", "Textures/smooth.jpg", 0.0)
{
   Planet::bump = false;
}

void Sun::render()
{
    textureMap->bind();

   glPushMatrix();
   //glColor3f(color[0], color[1], color[2]);
   glRotatef(90, 1, 0, 0);
   glScalef(size, size, size);
   //glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);
   mySphere2();
   textureMap->unbind();
   if (glowFlag)
      renderGlow();
   glPopMatrix();


}

void Sun::glow(float s)
{
	glPushMatrix();
	float color[3] = {1, 0, 0}; //red
	glColor4f(color[0], color[1], color[2], s);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);
	glutSolidSphere(.75, 10, 10);
	glPopMatrix();
}

void Sun::renderGlow()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	float scaler;
	int n;
	float range;
	float step;

	range = 2;
	n = range * 40 - 40;
	step = 1.0 / n;

	for (int i = n; i >= 0; --i)
	{
		scaler = range - .025*(float)i;

		glPushMatrix();
		glScalef(scaler, scaler, scaler);
		glow(step);
		glPopMatrix();
	}

	glDisable(GL_BLEND);
}