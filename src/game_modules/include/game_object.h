#pragma once

#include <glm/glm.hpp>


namespace GAME_NAMESPACE
{
	namespace GameModule
	{
		class GameObj
		{
		public:
			GameObj() = default;
			~GameObj() = default;
		private:
			glm::vec3 pos;
			glm::vec3 scale = {1.0f, 1.0f, 0.0f};
		};
	}
}
