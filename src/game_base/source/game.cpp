#include <functional>

#include "../include/game.h"

namespace GAME_NAMESPACE
{
	Game::Game()
		: m_isRunning(true)
	{
		init();
	}

	void Game::init()
	{
		CallbackData data;
		data.func = std::bind(&Game::onEvent, this, std::placeholders::_1);
		m_window = std::unique_ptr<Window>(new Window(data));
	}

	void Game::onEvent(Event& event)
	{
		switch (event.getType())
		{
			case EventType::CLOSE:
			{
				m_isRunning = false;

			}break;
			
			default:
			{}break;
		}
	}

	void Game::run()
	{
		while (m_isRunning)
		{
			m_window->update();
		}
	}
}
