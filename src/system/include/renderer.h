#pragma once

#include "shader.h"
#include "texture.h"

namespace GAME_NAMESPACE
{
	namespace System
	{
		class Renderer
		{
		public:
			Renderer();
			~Renderer() = default;

			void draw(glm::vec3& scale, Shader& shader);
			void draw(glm::vec3& scale, Shader& shader, Texture& texture);

			Renderer(const Renderer&) = delete;
			Renderer(const Renderer&&) = delete;
			Renderer& operator=(const Renderer&) = delete;
			Renderer& operator=(const Renderer&&) = delete;

		private:
			void init();

			unsigned int m_quadVAO;
		};
	}
}
