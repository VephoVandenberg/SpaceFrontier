#pragma once

#include "../game_object.h"

namespace GAME_NAMESPACE
{
	namespace GameModule
	{
		enum class MeteoriteType
		{
			Small = 1,
			Medium
		};

		namespace
		{
			constexpr unsigned int g_hitsForSmall = 1;
			constexpr unsigned int g_hitsForMedium = 3;
		}

		class System::Texture;

		class Player;
		class Enemy;

		class Meteorite : public GameObj
		{
		public:
			Meteorite(glm::vec3 pos, glm::vec3 orientation, System::Texture& texture, MeteoriteType type = MeteoriteType::Small);

			void update(
				float dt,
				Player& player, std::vector<Enemy>& enemies,
				const glm::vec3& cameraPos);
			void draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos) override;
			bool isOut(float left, float right, float bottom, float up) const;

			Meteorite() = default;
			~Meteorite() = default;
			Meteorite(Meteorite&&) = default;
			Meteorite& operator=(Meteorite&&) = default;

			Meteorite(const Meteorite&) = default;
			Meteorite& operator=(const Meteorite&) = default;

		private:
			float m_damage = 30.0f;

			struct MeteoriteInfo
			{
				unsigned int m_hitsToTake;
				MeteoriteType m_type;
			} m_meteoriteInfo;

			glm::vec3 m_velocity = { 0.0f, 0.0f, 0.0f };

			System::Texture& m_texture;
		};
	}
}
