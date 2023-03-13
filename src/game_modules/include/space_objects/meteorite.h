#pragma once

#include "space_object.h"

namespace GAME_NAMESPACE
{
	namespace GameModule
	{
		enum class MeteoriteType
		{
			Small,
			Medium
		};

		namespace
		{
			constexpr unsigned int g_hitsForSmall = 1;
			constexpr unsigned int g_hitsForMedium = 3;
		}

		class Meteorite : public SpaceObj
		{
		public:
			Meteorite(glm::vec3 pos, glm::vec3 scale, System::Texture& texture, MeteoriteType type = MeteoriteType::Small);

			void update(
				float dt,
				Player& player, std::vector<Enemy>& enemies,
				const glm::vec3& cameraPos) override;

			Meteorite() = default;
			~Meteorite() = default;
			Meteorite(Meteorite&&) = default;
			Meteorite& operator=(Meteorite&&) = default;

			Meteorite(const Meteorite&) = delete;
			Meteorite& operator=(const Meteorite&) = delete;

		private:
			struct MeteoriteInfo
			{
				unsigned int m_hitsToTake;
				MeteoriteType m_type;

				MeteoriteInfo(MeteoriteType type)
					: m_type(type)
				{
					switch (m_type)
					{
					case MeteoriteType::Small:
					{
						m_hitsToTake = g_hitsForSmall;
					}

					case MeteoriteType::Medium:
					{
						m_hitsToTake = g_hitsForMedium;
					}

					}
				}
			} m_meteoriteInfo;

			glm::vec3 m_velocity = { 0.0f, 0.0f, 0.0f };
		};
	}
}