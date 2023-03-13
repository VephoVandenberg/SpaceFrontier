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

		class Meteorite : public SpaceObj
		{
		public:
			Meteorite(glm::vec3 pos, glm::vec3 scale, System::Texture& texture);
			
			Meteorite() = default;
			~Meteorite() = default;
			Meteorite(Meteorite&&) = default;
			Meteorite& operator=(Meteorite&&) = default;

			Meteorite(const Meteorite&) = delete;
			Meteorite& operator=(const Meteorite&) = delete;

		private:
		};
	}
}