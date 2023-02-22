#pragma once

#include "../../system/include/renderer.h"

#include "UI/Button.h"

#include "scene.h"

namespace GAME_NAMESPACE
{
	namespace GameScene
	{
		class Menu : public Scene
		{
		public:
			Menu(float width, float height, System::Renderer& renderer);
			~Menu();

			void update(float dt, const glm::vec3& cameraView) override;
			void processInput(float dt, glm::vec3& cameraView, const glm::vec3& cursorPos, bool* const keys) override;
			
			inline Scenes nextScene() override { return m_nextScene; }
			inline Scenes getScene() override { return Scenes::MenuScene; }

			Menu(Menu&&) = default;
			Menu& operator=(Menu&&) = default;

			Menu() = delete;
			Menu(const Menu&) = delete;
			Menu& operator=(const Menu&) = delete;
		
		protected:
			void onAttach() override;
			void onDetatch() override;
			void render(const glm::vec3& cameraView) override;

		private:
			float m_width;
			float m_height;

			System::Renderer& m_renderer;

			GameModule::GameObj m_panel;
			GameScene::Button m_start;
			GameScene::Button m_exit;
		};
	}
}
