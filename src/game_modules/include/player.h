#pragma once

#include <glm/glm.hpp>
#include <list>

#include "../../system/include/renderer.h"
#include "../../system/include/shader.h"

#include "game_object.h"
#include "projectile.h"
#include "Enemy.h"

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

		class Player : public GameObj
		{
		public:
			Player(glm::vec3 scale, glm::vec3 pos, System::Texture& texture);

			Player() = default;
			~Player() = default;

			void update(float dt, float angle, float borderX, float borderY, MoveDir dir);
			void drawProjectiles(System::Shader& shader, System::Renderer& renderer);
			void draw(System::Shader& shader, System::Renderer& renderer, bool hasTexture = true) override;
			void shoot();
			void checkProjEnemyCoollision(Enemy& enemy);

			Player(const Player&) = delete;
			Player(Player&&) = delete;
			Player& operator=(const Player&) = delete;
			Player& operator=(Player&&) = delete;
			
		private:
			float m_health = 100.0f;
			float m_acceleration = 01.0f;
			glm::vec3 m_velocity = {0.0f, 0.0f, 0.0f};
			glm::vec3 m_cameraPos = { 0.0f, 0.0f, 0.0f };
			
			std::list<Projectile> m_projectiles;
		};
	}
}