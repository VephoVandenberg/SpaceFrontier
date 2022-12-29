#include <functional>

#include "../../system/include/resource_manager.h"	

#include "../include/game.h"

using namespace GAME_NAMESPACE;

Game::Game()
	: m_isRunning(true)
{
	init();
}

void Game::init()
{
	System::CallbackData data;
	data.func = std::bind(&Game::onEvent, this, std::placeholders::_1);

	m_window = std::unique_ptr<System::Window>(new System::Window(data));
	m_renderer = std::unique_ptr<System::Renderer>(new System::Renderer);

	System::ResourceManager::getInstance()
		.setShader("simple", "shaders/simple_shader.vert", "shaders/simple_shader.frag");

	System::ResourceManager::getInstance()
		.setTexture("textures/container.jpg");
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
		m_window->clearScreen();
		m_renderer->draw(System::ResourceManager::getInstance().getShader("simple"));
		m_window->update();
	}
}


