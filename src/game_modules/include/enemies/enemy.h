#pragma once

#include <list>
#include <vector>

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
			Chasing,
			Fleeing
		};

		class System::Texture;
		class Player;

		class Enemy : public GameObj
		{
		public:
			Enemy(glm::vec3 pos, glm::vec3 scale, System::Texture& texture);

			virtual void update(float dt, float borderX, float borderY, const glm::vec3& cameraPos, const Player& player);
			virtual void shoot();

			void updatePosition(float dt, bool isMovingForward);
			void draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos) override;
			void drawProjectiles(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos);
			int checkProjPlayerCoollision(const Player& player);

			bool checkMessWithEnemy(float dt, const float distanceToKeep, const Enemy& enemy, const Player& player);

			inline void takeDamage() { m_health--; }
			inline bool isAlive() const { return m_health > 0; }

			bool operator==(const Enemy& enemy);
			bool operator!=(const Enemy& enemy);

			Enemy() = default;
			virtual ~Enemy() = default;
			Enemy(Enemy&&) = default;
			Enemy& operator=(Enemy&&) = default;

			Enemy(const Enemy&) = delete;
			Enemy& operator=(const Enemy&) = delete;

		protected:
			virtual void idle(float dt, const Player& player);
			virtual void patroll(float dt, const Player& player);
			virtual void fight(float dt, const Player& player);
			virtual void flee(float dt, const Player& player);

		private:
			System::Texture m_texture;
			glm::vec3 m_velocity = { 0.0f, 0.0f, 0.0f };

			int m_health = 3;
			float m_timer = 0.0f;
			float m_shootingTimeGap = 0.0f;

			std::list<Projectile> m_projectiles;
			EnemyState m_state = EnemyState::Idle;

			bool m_isMessing = false;
		};
	}
}
