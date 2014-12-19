#include "Sun.h"
#include <Windows.h>
#include "GLee.h"
#include "BasicParticles.hpp"
#include "BasicParticleGenerators.hpp"
#include "ParticleUpdaters.hpp"
#include "glParticleRenderer.hpp"
ParticleSystem * m_system = new ParticleSystem(size_t(500));
GLParticleRenderer * renderP = new GLParticleRenderer();
Sun::Sun() : Planet(109, "Textures/sunmap.jpg", "Textures/smooth.jpg", 0.0)
{
   Planet::bump = false;
   auto timeUpdater = make_shared<updaters::BasicTimeUpdater>();
   m_system->addUpdater(timeUpdater);

   auto colorUpdater = make_shared<updaters::BasicColorUpdater>();
   m_system->addUpdater(colorUpdater);

   auto m_eulerUpdater = make_shared<updaters::EulerUpdater>();
   m_eulerUpdater->m_globalAcceleration = glm::vec4{ 0.0, -50.0, 0.0, 0.0 };
   m_system->addUpdater(m_eulerUpdater);

   auto particleEmitter = std::make_shared<ParticleEmitter>();
   {
      particleEmitter->m_emitRate = (float)500 * 0.45f;

      // pos:
      auto posGenerator = std::make_shared<generators::RoundPosGen>();
      //posGenerator->m_pos = glm::vec4{ 0.0, 0.0, 5, 0.0 };
      //posGenerator->m_maxStartPosOffset = glm::vec4{ 0.2, 0.0, 0, 0.0 };
      posGenerator->m_center = glm::vec4{ 0.0, 0.0, 0, 0.0 };
      posGenerator->m_radX = 11;
      posGenerator->m_radY = 11;
      particleEmitter->addGenerator(posGenerator);

      auto colGenerator = std::make_shared<generators::BasicColorGen>();
      colGenerator->m_minStartCol = glm::vec4{ 1, 0.647059, 0, 1.0 };
      colGenerator->m_maxStartCol = glm::vec4{ 1, 0.54902, 0, 1.0 };
      colGenerator->m_minEndCol = glm::vec4{ 1, 1.0, 1.0, 0.0 };
      colGenerator->m_maxEndCol = glm::vec4{ 1, 1.0, 1.0, 0.0 };
      particleEmitter->addGenerator(colGenerator);

      auto velGenerator = std::make_shared<generators::BasicVelGen>();
      velGenerator->m_minStartVel = glm::vec4{ 0.0f, 0.15f, 0.0f, 0.0f };
      velGenerator->m_maxStartVel = glm::vec4{ 0.0f, 0.45f, 0.0f, 0.0f };
      particleEmitter->addGenerator(velGenerator);

      auto timeGenerator = std::make_shared<generators::BasicTimeGen>();
      timeGenerator->m_minTime = 1.0;
      timeGenerator->m_maxTime = 1.5;
      particleEmitter->addGenerator(timeGenerator);
   }
   m_system->addEmitter(particleEmitter);
   renderP->generate(m_system, false);
}

void Sun::render()
{
   if (!partShader)
      partShader = new Shader("particle.vert", "particle.frag", true);

   float specular2[] = { 1.0, 1.0, 1.0, 1.0 };
   float ambient2[] = { .5, .5, .5, 1.0 };
   float position2[] = { 0, 0.0, 0.0, 1.0 };	// lightsource position

   // Generate light source:
   glLightfv(GL_LIGHT0, GL_POSITION, position2);
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient2);
   glLightfv(GL_LIGHT0, GL_SPECULAR, specular2);
   GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glEnable(GL_LIGHT0);


   m_system->update(.01);
   renderP->update();
   glPushMatrix();

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE);
   //glLoadIdentity();
   partShader->bind();
   glPointSize(2);
   glScalef(111, 111, 111);
   renderP->render();
   glDisable(GL_BLEND);
   partShader->unbind();
   glPopMatrix();

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
   color[0] = 0;
   color[1] = 0;
   color[2] = 0;
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);
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