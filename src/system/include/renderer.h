#pragma once

#include "shader.h"

namespace GAME_NAMESPACE
{
	namespace System
	{
		class Renderer
		{
		public:
			Renderer();
			~Renderer() = default;

			void draw(Shader& shader);

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
