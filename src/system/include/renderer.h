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

			void draw(float angle, glm::vec3& pos, glm::vec3& scale, glm::vec3& color, const glm::vec3& viewDir, Shader& shader);
			void draw(float angle, glm::vec3& pos, glm::vec3& scale, const glm::vec3& viewDir, Shader& shader, Texture& texture);
			void draw(float angle, glm::vec3& pos, glm::vec3& scale, glm::vec3& color, const glm::vec3& viewDir, Shader& shader, Texture& texture);

			Renderer(const Renderer&) = delete;
			Renderer(const Renderer&&) = delete;
			Renderer& operator=(const Renderer&) = delete;
			Renderer& operator=(const Renderer&&) = delete;

		private:
			void init();
			void setBaseUniforms(float angle, glm::vec3& pos, glm::vec3& scale, const glm::vec3& viewDir, Shader& shader) const;

			unsigned int m_quadVAO;
		};
	}
}
