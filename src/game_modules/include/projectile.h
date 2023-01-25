#pragma once

#include <glm/glm.hpp>

#include "../../system/include/shader.h"

#include "game_object.h"

namespace GAME_NAMESPACE
{
	namespace GameModule
	{
		class Projectile : public GameObj
		{
		public:
			Projectile(glm::vec3 pos, glm::vec3 scale, glm::vec3 color, glm::vec3 velocitiy, float angle);

			void update(float dt);

			Projectile() = default;
			~Projectile() = default;
			Projectile(const Projectile& proj) = default;
			Projectile& operator=(const Projectile& proj) = default;
		private:
			glm::vec3 m_velocity;
			glm::vec3 m_additionalVelocity = { 0.0f, 0.0f, 0.0f };
		};
	}
}