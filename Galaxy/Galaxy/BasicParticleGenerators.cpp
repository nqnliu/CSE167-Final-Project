#include "BasicParticleGenerators.hpp"
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <glm/common.hpp>
#include <glm/gtc/random.hpp>
#define M_PI 3.14159265358979323846
namespace particles
{
   namespace generators
   {
      void BoxPosGen::generate(double dt, ParticleData *p, size_t startId, size_t endId)
      {
         glm::vec4 posMin{ m_pos.x - m_maxStartPosOffset.x, m_pos.y - m_maxStartPosOffset.y, m_pos.z - m_maxStartPosOffset.z, 1.0 };
         glm::vec4 posMax{ m_pos.x + m_maxStartPosOffset.x, m_pos.y + m_maxStartPosOffset.y, m_pos.z + m_maxStartPosOffset.z, 1.0 };

         for (size_t i = startId; i < endId; ++i)
         {
            p->m_pos[i] = glm::linearRand(posMin, posMax);
         }
      }

      void RoundPosGen::generate(double dt, ParticleData *p, size_t startId, size_t endId)
      {
         /*for (size_t i = startId; i < endId; ++i)
         {
            double ang = glm::linearRand(0.0, M_PI*2.0);
            p->m_pos[i] = m_center + glm::vec4(m_radX*sin(ang), m_radY*cos(ang), m_radY*cos(ang)*sin(ang), 1.0);
         }*/
         for (size_t i = startId; i < endId; ++i)
         {
            double x1 = glm::linearRand(-1.0, 1.0);
            double x2 = glm::linearRand(-1.0, 1.0);
            while (((x1 * x1) + (x2 * x2)) >= 1)
            {
               x1 = glm::linearRand(-1.0, 1.0);
               x2 = glm::linearRand(-1.0, 1.0);
            }
            double x = 2 * x1 * (sqrt(1 - (x1 * x1) - (x2 * x2)));
            double y = 2 * x2 * (sqrt(1 - (x1 * x1) - (x2 * x2)));
            double z = 1 - 2 * ((x1 * x1) + (x2 * x2));
            p->m_pos[i] = m_center + glm::vec4(x, y, z, 1.0);
         }
      }

      void BasicColorGen::generate(double dt, ParticleData *p, size_t startId, size_t endId)
      {
         for (size_t i = startId; i < endId; ++i)
         {
            p->m_startCol[i] = glm::linearRand(m_minStartCol, m_maxStartCol);
            p->m_endCol[i] = glm::linearRand(m_minEndCol, m_maxEndCol);
         }
      }

      void BasicVelGen::generate(double dt, ParticleData *p, size_t startId, size_t endId)
      {
         for (size_t i = startId; i < endId; ++i)
         {
            p->m_vel[i] = glm::linearRand(m_minStartVel, m_maxStartVel);
         }
      }

      void SphereVelGen::generate(double dt, ParticleData *p, size_t startId, size_t endId)
      {
         float phi, theta, v, r;
         for (size_t i = startId; i < endId; ++i)
         {
            phi = glm::linearRand(-M_PI, M_PI);
            theta = glm::linearRand(-M_PI, M_PI);
            v = glm::linearRand(m_minVel, m_maxVel);

            r = v*sinf(phi);
            p->m_vel[i].z = v*cosf(phi);
            p->m_vel[i].x = r*cosf(theta);
            p->m_vel[i].y = r*sinf(theta);
         }
      }

      void BasicTimeGen::generate(double dt, ParticleData *p, size_t startId, size_t endId)
      {
         for (size_t i = startId; i < endId; ++i)
         {
            p->m_time[i].x = p->m_time[i].y = glm::linearRand(m_minTime, m_maxTime);
            p->m_time[i].z = (float)0.0;
            p->m_time[i].w = (float)1.0 / p->m_time[i].x;
         }
      }
   }
}