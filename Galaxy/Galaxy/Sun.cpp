#include "Sun.h"
#include <Windows.h>
#include "GLee.h"

Sun::Sun()
{
}

void Sun::render()
{
   glPushMatrix();
   float specular[] = { 0.0, 0.0, 0.0, 1.0 };
   float ambient[] = { .5, .5, .5, 1.0 };
   float position[] = { 0, 0, 0.0, 1.0 };	// lightsource position
   float shininess[] = { 1.0 };
   // Generate light source:
   glLightfv(GL_LIGHT0, GL_POSITION, position);
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
   GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glEnable(GL_LIGHT0);

   float color[3] = { .5, 0, 0 }; //red
   glColor3f(color[0], color[1], color[2]);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);
   glutSolidSphere(1.0, 50, 50);
   glPopMatrix();
}

void Sun::glow(float s)
{
	glPushMatrix();
	float color[3] = {1, 0, 0}; //red
	glColor4f(color[0], color[1], color[2], s);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);
	glutSolidSphere(1.0, 50, 50);
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