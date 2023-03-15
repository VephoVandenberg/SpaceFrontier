#pragma once

#include <list>
#include <vector>

#include "marker.h"

#include "../game_object.h"
#include "../projectile.h"

namespace GAME_NAMESPACE
{
	namespace GameModule
	{
		enum class EnemyState
		{
			Patrolling,
			Fighting,
			Chasing,
			Fleeing
		};

		class System::Texture;
		class Player;
		class Meteorite;
		class Asteroid;

		class Enemy : public GameObj
		{
		public:
			Enemy(glm::vec3 pos, glm::vec3 scale, System::Texture& texture);

			virtual void update(
				float dt, 
				float borderX, float borderY, 
				Player& player, 
				const glm::vec3& cameraPos, 
				const std::vector<Enemy>& enemies, 
				const std::list<Meteorite>& meteorites, const std::vector<Asteroid>& asteroids);
			virtual void shoot();

			void draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos) override;
			void drawProjectiles(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos);
			void drawMarker(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos);

			inline void takeDamage(unsigned int damage = 1) { m_health -= damage; }
			inline bool isAlive() const { return m_health > 0; }

			bool operator==(const Enemy& enemy) const;
			bool operator!=(const Enemy& enemy) const;

			Enemy() = default;
			virtual ~Enemy() = default;
			Enemy(Enemy&&) = default;
			Enemy& operator=(Enemy&&) = default;

			Enemy(const Enemy&) = delete;
			Enemy& operator=(const Enemy&) = delete;

		protected:
			// Boid rules
			glm::vec3 alignment(const std::vector<Enemy>& enemies) const;
			glm::vec3 cohesion(const std::vector<Enemy>& enemies) const;
			glm::vec3 chaseAlignment(const std::vector<Enemy>& enemies, const Player& player) const;
			glm::vec3 separation(const std::vector<Enemy>& enemies) const;
			glm::vec3 meteoriteSeparation(const std::list<Meteorite>& meteorites) const;
			glm::vec3 asteroidSeparation(const std::vector<Asteroid>& asteroids) const;
			glm::vec3 playerSeparation(const Player& player) const;
			glm::vec3 patrollVector() const;

		private:
			System::Texture m_texture;
			glm::vec3 m_velocity = { 0.0f, 0.0f, 0.0f };
			glm::vec3 m_orientation = { 0.0f, 0.0f, 0.0f };

			int m_health = 3;
			float m_timer = 0.0f;
			float m_shootingTimeGap = 0.0f;

			std::list<Projectile> m_projectiles;
			EnemyState m_state = EnemyState::Patrolling;

			Marker m_marker;
		};
	}
}
