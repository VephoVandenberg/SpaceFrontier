#pragma once

#include <memory>
#include <vector>

#include "../../system/include/event.h"
#include "../../system/include/window.h"
#include "../../system/include/renderer.h"

#include "../../scenes/include/scene.h"

#include "../../game_modules/include/player.h"
#include "../../game_modules/include/enemies/enemy.h"

namespace GAME_NAMESPACE
{
	class Game
	{
	public:
		Game();
		~Game() = default;

		void run();

		Game(const Game&) = delete;
		Game(Game&&) = delete;
		Game& operator=(const Game&) = delete;
		Game& operator=(Game&&) = delete;

	private:
		void init();
		void initShaders();
		void initTextures();
		void switchScene();
		void onEvent(System::Event& event);

		std::unique_ptr<System::Window> m_window = nullptr;
		std::unique_ptr<System::Renderer> m_renderer = nullptr;
		std::unique_ptr<GameScene::Scene> m_scene = nullptr;
		std::unique_ptr<GameModule::Player> m_player = nullptr;
		
		std::vector<GameModule::Enemy> m_enemies;

		bool m_isRunning = false;
		bool m_keys[1024];
	};
}