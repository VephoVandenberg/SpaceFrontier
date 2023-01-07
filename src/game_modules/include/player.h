#pragma once

#include <glm/glm.hpp>

#include "game_object.h"

namespace GAME_NAMESPACE
{
	namespace GameModule
	{
		class Player : public GameObj
		{
		public:
			Player(glm::vec3 scale, glm::vec3 pos, System::Texture& texture);

			Player() = default;
			~Player() = default;

			Player(const Player&) = delete;
			Player& operator=(const Player&) = delete;
			Player& operator=(const Player&&) = delete;
			Player(const Player&&) = delete;
			
			void init();
		private:
			float health = 100.0f;
		};
	}
}