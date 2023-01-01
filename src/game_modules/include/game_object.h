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
			GameObj(glm::vec3 scale);
			GameObj(glm::vec3 scale, System::Texture& texture);

			void draw(System::Shader& shader, System::Renderer& renderer,
				glm::vec3 pos, glm::vec3 rotation = { 0.0f, 0.0f, 0.0f });

			GameObj() = default;
			~GameObj() = default;
			GameObj(const GameObj&) = default;
			GameObj& operator=(const GameObj&) = default;

		private:
			System::Texture m_texture;

			glm::vec3 m_color = {1.0f, 1.0f, 1.0f};
			glm::vec3 m_scale = {1.0f, 1.0f, 0.0f};
		};
	}
}
