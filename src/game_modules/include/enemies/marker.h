#pragma once

#include <glm/glm.hpp>

#include "../game_object.h"

namespace GAME_NAMESPACE
{
	namespace GameModule
	{
		class Marker : public GameObj
		{
		public:
			Marker(glm::vec3 color, float angle = 0.0f);

			void update(float dt, glm::vec3 playerPos, glm::vec3 enemyPos);

			Marker() = default;
			~Marker() = default;
			Marker(Marker&&) = default;
			Marker& operator=(Marker&&) = default;

			Marker(const Marker&) = delete;
			Marker& operator=(const Marker&) = delete;
		
		private:
		};
	}
}
