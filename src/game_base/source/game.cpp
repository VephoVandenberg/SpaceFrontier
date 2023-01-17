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
		.setTexture("simple", "textures/container.jpg");

	auto& shader = System::ResourceManager::getInstance().getShader("simple");
	shader.use();

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_window->getWidth()),
		static_cast<float>(m_window->getHeight()), 0.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(static_cast<float>(m_window->getWidth()) / 2.0f,
		static_cast<float>(m_window->getHeight()) / 2.0f, 0.0f));
	glm::mat4 projView = projection * view;

	m_player = std::unique_ptr<GameModule::Player>(new GameModule::Player({ 50.0f, 50.0f, 0.0f }, { 200.0f, 200.0f, 0.0f },
		System::ResourceManager::getInstance().getTexture("simple")));

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
	{
		auto& key = dynamic_cast<System::KeyPressEvent&>(event).key;
		m_keys[key] = true;
	}break;

	case System::EventType::KEY_REPEAT:
	{
		auto& key = dynamic_cast<System::KeyRepeatEvent&>(event).key;
		m_keys[key] = true;
	}break;

	case System::EventType::KEY_RELEASE:
	{
		auto& key = dynamic_cast<System::KeyReleaseEvent&>(event).key;
		m_keys[key] = false;
	}break;

	default:
	{}break;
	}
}

void Game::run()
{
	float previousFrame = 0.0f;
	while (m_isRunning)
	{
		float currentFrame = glfwGetTime();
		float dt = currentFrame - previousFrame;
		previousFrame = currentFrame;
		m_window->clearScreen();

		render();

		m_window->update();

		processInput(dt);
	}
}

void Game::render()
{
	m_player->draw(System::ResourceManager::getInstance().getShader("simple"), *m_renderer);
}

void Game::processInput(float dt)
{
	float angle = 0.0f;
	GameModule::MoveDir moveDir = GameModule::MoveDir::None;;
	if (m_keys[GLFW_KEY_A])
	{
		angle -= 0.005f;
	}
	if (m_keys[GLFW_KEY_D])
	{
		angle += 0.005f;
	}
	if (m_keys[GLFW_KEY_W])
	{
		moveDir = GameModule::MoveDir::Up;
	}
	if (m_keys[GLFW_KEY_S])
	{
		moveDir = GameModule::MoveDir::Bottom;
	}
	m_player->update(dt, angle, moveDir);
}
