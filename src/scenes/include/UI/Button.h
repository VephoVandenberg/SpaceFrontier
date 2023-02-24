#pragma once

#include "../../../system/include/texture.h"

#include "../../../game_modules/include/game_object.h"

namespace GAME_NAMESPACE
{
	namespace GameScene
	{
		class Button : public GameModule::GameObj
		{
		public:
			Button(glm::vec3 pos, glm::vec3 scale, glm::vec3 color, System::Texture& texture);

			void changeColor();
			void draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos) override;

			inline void click() { m_isClicked = true; }
			inline void makeTarget() { m_isTarget = true; }
			inline void loosenClick() { m_isClicked = false; }
			inline void loosenTarget() { m_isTarget = false; }

			Button() = default;
			~Button() = default;
			Button(const Button&) = default;
			Button& operator=(const Button&) = default;
			Button(Button&&) = default;
			Button& operator=(Button&&) = default;

		private:
			bool m_isClicked = false;
			bool m_isTarget = false;

			System::Texture m_texture;
		};
	}
}