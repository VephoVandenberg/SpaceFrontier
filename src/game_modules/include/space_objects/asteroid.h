#pragma once

#pragma once

#include "../game_object.h"

namespace GAME_NAMESPACE
{
	namespace GameModule
	{
		enum class AsteroidType
		{
			Medium = 1,
			Large,
			FuckinHuge
		};

		namespace
		{
			constexpr unsigned int g_hitsForMedium = 15;
			constexpr unsigned int g_hitsForLarge = 3;
		}

		class System::Texture;

		class Player;
		class Enemy;

		class Asteroid : public GameObj
		{
		public:
			Asteroid(glm::vec3 pos, glm::vec3 orientation, System::Texture& texture, AsteroidType type = AsteroidType::FuckinHuge);

			void update(
				float dt,
				Player& player, std::vector<Enemy>& enemies,
				const glm::vec3& cameraPos);
			void draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos) override;
			bool isOut(float left, float right, float bottom, float up) const;

			Asteroid() = default;
			~Asteroid() = default;
			Asteroid(Asteroid&&) = default;
			Asteroid& operator=(Asteroid&&) = default;

			Asteroid(const Asteroid&) = default;
			Asteroid& operator=(const Asteroid&) = default;

		private:
			float m_damage = 30.0f;

			struct AsteroidInfo
			{
				unsigned int m_hitsToTake;
				AsteroidType m_type;
			} m_asteroidInfo;

			glm::vec3 m_velocity = { 0.0f, 0.0f, 0.0f };

			System::Texture& m_texture;
		};
	}
}
