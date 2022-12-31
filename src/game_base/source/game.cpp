#include <functional>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

	auto& shader = System::ResourceManager::getInstance().getShader("simple");
	shader.use();

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_window->getWidth()), 
		static_cast<float>(m_window->getHeight()), 0.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(static_cast<float>(m_window->getWidth())/2.0f, 
		static_cast<float>(m_window->getHeight())/2.0f, 0.0f));
	glm::mat4 projView = projection * view;
	shader.setMatrix("uProjView", projView);
}

void Game::onEvent(System::Event& event)
{
	switch (event.getType())
	{
	case System::EventType::CLOSE:
	{
		m_isRunning = false;
	}break;

	case System::EventType::KEY_PRESS:
	case System::EventType::KEY_REPEAT:
	case System::EventType::KEY_RELEASE:
	{
		auto key = dynamic_cast<System::KeyPressEvent&>(event).key;
		processInput(key, event.getType());
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
		
		render();

		m_window->update();
	}
}

void Game::render()
{
	auto tmpScale = glm::vec3(200.0f, 300.0f, 0.0f);
	m_renderer->draw(tmpScale, System::ResourceManager::getInstance().getShader("simple"));
}

void Game::processInput(int key, System::EventType event)
{
	switch (key)
	{
	case GLFW_KEY_Q:
	{

	}break;
	
	case GLFW_KEY_E:
	{

	}break;

	default:
	{}break;
	}
}
