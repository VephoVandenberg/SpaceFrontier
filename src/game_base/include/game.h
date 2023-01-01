#pragma once

#include <memory>
#include <vector>

#include "../../system/include/event.h"
#include "../../system/include/window.h"
#include "../../system/include/renderer.h"

#include "../../game_modules/include/game_object.h"

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
		void processInput(int key, System::EventType event);
		void render();

		std::unique_ptr<System::Window> m_window = nullptr;
		std::unique_ptr<System::Renderer> m_renderer = nullptr;

		std::vector<GameModule::GameObj> m_objects{};

		bool m_isRunning = false;
	};
}