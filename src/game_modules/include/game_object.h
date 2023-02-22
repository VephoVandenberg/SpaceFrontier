#pragma once

#include <glm/glm.hpp>

#include "../../system/include/renderer.h"
#include "../../system/include/shader.h"

namespace GAME_NAMESPACE
{
	namespace GameModule
	{
		class GameObj
		{
		public:
			GameObj(glm::vec3 pos, glm::vec3 scale, glm::vec3 color = {0.0f, 0.0f, 0.0f}, float m_angle = 0.0f);

			virtual void draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos);
			bool checkCollision(const GameObj& obj) const;

			inline glm::vec3 getPos() const { return m_pos; }
			inline glm::vec3 getScale() const { return m_scale; }

			GameObj() = default;
			virtual ~GameObj() = default;
			GameObj(const GameObj&) = default;
			GameObj& operator=(const GameObj&) = default;
			GameObj(GameObj&&) = default;
			GameObj& operator=(GameObj&&) = default;

		protected:
			glm::vec3 m_pos = { 0.0f, 0.0f, 0.0f };
			glm::vec3 m_scale = { 1.0f, 1.0f, 0.0f };
			glm::vec3 m_color = { 0.0f, 0.0f, 0.0f };
			float m_angle;
		};
	}
}
