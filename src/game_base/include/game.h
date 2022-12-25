#pragma once

#include <memory>

#include "../../system/include/event.h"
#include "../../system/include/window.h"

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
		void onEvent(Event& event);

		std::unique_ptr<Window> m_window;
		bool m_isRunning = false;
	};
}