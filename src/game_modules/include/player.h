#pragma once

#include <glm/glm.hpp>
#include <list>

#include "../../system/include/texture.h"

#include "game_object.h"
#include "enemies/enemy.h"

namespace GAME_NAMESPACE
{

	namespace GameModule
	{
		enum class MoveDir
		{
			Up = -1,
			None,
			Bottom
		};

		class System::Renderer;
		class System::Shader;
		class Projectile;

		class Player : public GameObj
		{
		public:
			Player(glm::vec3 scale, glm::vec3 pos, System::Texture& texture);

			Player() = default;
			~Player() = default;

			void update(float dt, float da, float borderX, float borderY, glm::vec3& cameraPos, MoveDir dir);
			void drawProjectiles(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos);
			void draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos) override;
			void checkProjEnemyCoollision(Enemy& enemy);
			void reset(glm::vec3 pos);
			void shoot();

			inline void takeDamage(int damage) { m_health -= damage; }
			inline bool isAlive() const { return m_health > 0.0f; }
			inline glm::vec3 getVelocity() const { return m_velocity; }

			Player(const Player&) = delete;
			Player(Player&&) = delete;
			Player& operator=(const Player&) = delete;
			Player& operator=(Player&&) = delete;
			
		private:
			System::Texture m_texture;

			float m_health = 10.0f;
			float m_velocityCoeff = 1.0f;

			glm::vec3 m_velocity = { 0.0f, 0.0f, 0.0f} ;

			std::list<Projectile> m_projectiles;
		};
	}
}
