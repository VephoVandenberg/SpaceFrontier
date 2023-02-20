#pragma once

#include <list>

#include "../../../system/include/texture.h"

#include "../game_object.h"
#include "../projectile.h"

namespace GAME_NAMESPACE
{
	namespace GameModule
	{
		enum class EnemyState
		{
			Idle = 1,
			Patrolling,
			Fighting,
			Fleeing
		};

		class Enemy : public GameObj
		{
		public:
			Enemy(glm::vec3 pos, glm::vec3 scale, System::Texture& texture);

			virtual void update(float dt, float borderX, float borderY, glm::vec3& cameraPos, const GameObj& playerObj);
			virtual void shoot();
			void draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos) override;
			void drawProjectiles(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos);
			int checkProjPlayerCoollision(const GameObj& playerObj);

			inline void takeDamage() { m_health--; }
			inline bool isAlive() const { return m_health > 0; }

			Enemy() = default;
			virtual ~Enemy() = default;
			Enemy(Enemy&&) = default;
			Enemy& operator=(Enemy&&) = default;
			
			Enemy(const Enemy&) = delete;
			Enemy& operator=(const Enemy&) = delete;

		protected:
			void idle(const GameObj& playerObj);
			void patroll(float dt, const GameObj& playerObj);
			void fight(float dt, const GameObj& playerObj);
			void flee();

		private:
			System::Texture m_texture;
			glm::vec3 m_velocity = { 0.0f, 0.0f, 0.0f };

			int m_health = 3;
			float m_timer = 0.0f;
			float m_shootingTimeGap = 0.0f;

			std::list<Projectile> m_projectiles;
			EnemyState m_state = EnemyState::Idle;
		};
	}
}