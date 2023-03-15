#pragma once

#pragma once

#include <map>

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

		class System::Texture;

		class Player;
		class Enemy;

		class Asteroid : public GameObj
		{
		public:
			Asteroid(glm::vec3 pos, System::Texture& texture, AsteroidType type = AsteroidType::FuckinHuge);

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

			Asteroid(const Asteroid&) = delete;
			Asteroid& operator=(const Asteroid&) = delete;

			static std::map<const AsteroidType, const unsigned int> s_asteroidSizes;

		private:
			float m_damage = 30.0f;

			struct AsteroidInfo
			{
				AsteroidType m_type;
			} m_asteroidInfo;

			System::Texture& m_texture;
		};
	}
}
