#pragma once

#include "../game_object.h"

namespace GAME_NAMESPACE
{
	namespace GameModule
	{
		class System::Texture;

		class SpaceObj : public GameObj
		{
		public:
			SpaceObj(glm::vec3 pos, glm::vec3 scale, System::Texture& texture);

			virtual ~SpaceObj() = default;
			SpaceObj(SpaceObj&&) = default;
			SpaceObj& operator=(SpaceObj&&) = default;

			SpaceObj() = delete;
			SpaceObj(const SpaceObj&) = delete;
			SpaceObj& operator=(const SpaceObj&) = delete;

		protected:
			float m_gravityForce;
			unsigned int m_damage = 5;

			System::Texture& m_texture;
		};
	}
}