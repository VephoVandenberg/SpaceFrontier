#pragma once

#include <glm/glm.hpp>

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
			bool isOut(float left, float right, float bottom, float up) const;

			Projectile() = default;
			~Projectile() = default;
			Projectile(Projectile&&) = default;
			Projectile& operator=(Projectile&&) = default;

			Projectile& operator=(const Projectile&) = delete;
			Projectile(const Projectile&) = delete;

		private:
			glm::vec3 m_velocity = { 0.0f, 0.0f, 0.0f };
			glm::vec3 m_additionalVelocity = { 0.0f, 0.0f, 0.0f };
		};
	}
}
