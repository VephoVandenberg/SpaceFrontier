#pragma once

#include <glm/glm.hpp>

#include "../../system/include/shader.h"
#include "../../system/include/texture.h"

#include "game_object.h"

namespace GAME_NAMESPACE
{
	namespace GameModule
	{
		class Projectile : public GameObj
		{
		public:
			Projectile();
		private:
			glm::vec3 m_pos;
			glm::vec3 m_color;

			System::Texture texture;
		};
	}
}