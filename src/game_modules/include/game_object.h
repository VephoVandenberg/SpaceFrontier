#pragma once

#include <glm/glm.hpp>

#include "../../system/include/renderer.h"
#include "../../system/include/shader.h"
#include "../../system/include/texture.h"

namespace GAME_NAMESPACE
{
	namespace GameModule
	{
		class GameObj
		{
		public:
			GameObj(glm::vec3 scale, glm::vec3 pos, float m_angle = 0.0f);
			GameObj(glm::vec3 scale, glm::vec3 pos, System::Texture& texture, float m_angle = 0.0f);

			virtual void draw(System::Shader& shader, System::Renderer& renderer, bool hasTexture = true);
			virtual void update(glm::vec3 deltaPos , float angle);
			bool checkCollision(const GameObj& obj) const;

			GameObj() = default;
			virtual ~GameObj() = default;
			GameObj(const GameObj&) = default;
			GameObj& operator=(const GameObj&) = default;
			GameObj(GameObj&&) = default;
			GameObj& operator=(GameObj&&) = default;
		protected:
			glm::vec3 m_pos = { 0.0f, 0.0f, 0.0f };
			glm::vec3 m_color = { 1.0f, 1.0f, 1.0f };
			glm::vec3 m_scale = { 1.0f, 1.0f, 0.0f };
			float m_angle;
		private:
			System::Texture m_texture;

		};
	}
}
