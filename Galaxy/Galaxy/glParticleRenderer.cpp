#include "glParticleRenderer.hpp"
#include "BasicParticles.hpp"

#include <assert.h>
#include "main.h"

namespace particles
{
	void GLParticleRenderer::generate(ParticleSystem *sys, bool)
	{
		assert(sys != nullptr);

		m_system = sys;

		const size_t count = sys->numAllParticles();

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &m_bufPos);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufPos);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 4 * count, nullptr, GL_STREAM_DRAW);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, (4)*sizeof(float), (void *)((0)*sizeof(float)));
		

		glGenBuffers(1, &m_bufCol);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufCol);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 4 * count, nullptr, GL_STREAM_DRAW);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, (4)*sizeof(float), (void *)((0)*sizeof(float)));

		glBindVertexArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void GLParticleRenderer::destroy()
	{
		if (m_bufPos != 0)
		{
			glDeleteBuffers(1, &m_bufPos);
			m_bufPos = 0;
		}

		if (m_bufCol != 0)
		{
			glDeleteBuffers(1, &m_bufCol);
			m_bufCol = 0;
		}
	}

	void GLParticleRenderer::update()
	{
		assert(m_system != nullptr);
		assert(m_bufPos > 0 && m_bufCol > 0);

		const size_t count = m_system->numAliveParticles();
		if (count > 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_bufPos);
			float *ptr = (float *)(m_system->finalData()->m_pos.get());
			glBufferSubData(GL_ARRAY_BUFFER, 0, count*sizeof(float)* 4, ptr);

			glBindBuffer(GL_ARRAY_BUFFER, m_bufCol);
			ptr = (float*)(m_system->finalData()->m_col.get());
			glBufferSubData(GL_ARRAY_BUFFER, 0, count*sizeof(float)* 4, ptr);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}

	void GLParticleRenderer::render()
	{
      const size_t count = m_system->numAliveParticles();

      glBegin(GL_POINTS);
      for (int i = 0; i < count; i++)
      {
         float x = m_system->finalData()->m_pos[i].x;
         float y = m_system->finalData()->m_pos[i].y;
         float z = m_system->finalData()->m_pos[i].z;
         float cx = m_system->finalData()->m_col[i].x;
         float cy = m_system->finalData()->m_col[i].y;
         float cz = m_system->finalData()->m_col[i].z;
         glColor3f(m_system->finalData()->m_col[i].x, m_system->finalData()->m_col[i].y, m_system->finalData()->m_col[i].z);
         glVertex3f(x, y, z);
      }
      glEnd();
      /*
		glBindVertexArray(m_vao);

		const size_t count = m_system->numAliveParticles();
      glColor3f(1.0, 0.0, 1.0);
		if (count > 0)
			glDrawArrays(GL_POINTS, 0, count);

		glBindVertexArray(0);*/
	}
}