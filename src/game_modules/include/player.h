#pragma once

#include <glm/glm.hpp>

#include "game_object.h"

namespace GAME_NAMESPACE
{
	namespace GameModule
	{
		enum class MoveDir
		{
			Up = -1,
			None,
			Bottom
		};

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
			void update(float dt, float angle, MoveDir dir);
		private:
			float m_health = 100.0f;
			float m_acceleration = 0.01f;
			glm::vec3 m_velocity = {0.0f, 0.0f, 0.0f};
		};
	}
}