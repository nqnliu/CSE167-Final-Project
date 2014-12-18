#include "particleRenderer.hpp"
#include "glParticleRenderer.hpp"

#include <string>

namespace particles
{
	std::shared_ptr<IParticleRenderer> RendererFactory::create(const char *name)
	{
		std::string renderer{ name };

		if (renderer == "gl")
			return std::make_shared<GLParticleRenderer>();

		return nullptr;
	}
}