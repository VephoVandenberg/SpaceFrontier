#pragma once

#include <memory>
#include <vector>

#include "../../system/include/event.h"
#include "../../system/include/window.h"
#include "../../system/include/renderer.h"

#include "../../game_modules/include/player.h"

namespace GAME_NAMESPACE
{
	class Game
	{
	public:
		Game();
		~Game() = default;

		void run();

		Game(const Game&) = delete;
		Game(const Game&&) = delete;
		Game& operator=(const Game&) = delete;
		Game& operator=(const Game&&) = delete;

	private:
		void init();
		void onEvent(System::Event& event);
		void processInput(float dt);
		void render();

		std::unique_ptr<System::Window> m_window = nullptr;
		std::unique_ptr<System::Renderer> m_renderer = nullptr;

		std::unique_ptr<GameModule::Player> m_player = nullptr;


		bool m_isRunning = false;
		bool m_keys[1024];
	};
}