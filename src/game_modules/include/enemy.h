#pragma once

#include <deque>

#include "../../system/include/texture.h"

#include "game_object.h"
#include "projectile.h"

namespace GAME_NAMESPACE
{
	namespace GameModule
	{
		class Enemy : public GameObj
		{
		public:
			Enemy(glm::vec3 pos, glm::vec3 scale, System::Texture& texture);

			void update(float dt);
			void shoot();

			Enemy() = default;
			~Enemy() = default;
			Enemy(Enemy&& enemy) = default;
			Enemy& operator=(Enemy&&) = default;
			Enemy(const Enemy& enemy) = delete;
			Enemy& operator=(const Enemy& enemy) = default;

		private:
			glm::vec3 m_velocity = { 0.0f, 0.0f, 0.0f };

			std::deque<Projectile> m_projectiles;
		};
	}
}