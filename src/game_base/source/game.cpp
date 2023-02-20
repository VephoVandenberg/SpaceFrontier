#include <functional>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../system/include/resource_manager.h"	

#include "../include/game.h"

using namespace GAME_NAMESPACE;


constexpr glm::vec3 g_playerShipSize = { 80.0f, 80.0f, 0.0f };
constexpr glm::vec3 g_baseEnemySize = { 80.0f, 80.0f, 0.0f };
constexpr float g_deltaAngle = 2.0f;

glm::vec3 s_cameraView = { 0.0f, 0.0f, 0.0f };


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
		.setShader("base_obj", "shaders/base_obj_shader.vert", "shaders/base_obj_shader.frag");
	System::ResourceManager::getInstance()
		.setShader("base_proj", "shaders/base_proj_shader.vert", "shaders/base_proj_shader.frag");

	System::ResourceManager::getInstance()
		.setTexture("player", "textures/player_ship.png");
	System::ResourceManager::getInstance()
		.setTexture("enemy_base", "textures/enemy_ship.png");


	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_window->getWidth()),
		static_cast<float>(m_window->getHeight()), 0.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	auto playerPos = glm::vec3(m_window->getWidth() / 2.0f, m_window->getHeight() / 2.0f, 0.0f);
	m_player = std::unique_ptr<GameModule::Player>(new GameModule::Player(playerPos, g_playerShipSize,
		System::ResourceManager::getInstance().getTexture("player")));

	initEnemies();

	System::ResourceManager::getInstance().getShader("base_obj").use();
	System::ResourceManager::getInstance().getShader("base_obj").setMatrix("uProjection", projection);
	System::ResourceManager::getInstance().getShader("base_obj").setMatrix("uView", view);
	System::ResourceManager::getInstance().getShader("base_obj").unbind();

	System::ResourceManager::getInstance().getShader("base_proj").use();
	System::ResourceManager::getInstance().getShader("base_proj").setMatrix("uProjection", projection);
	System::ResourceManager::getInstance().getShader("base_proj").setMatrix("uView", view);
	System::ResourceManager::getInstance().getShader("base_proj").unbind();
} 

void Game::initEnemies()
{
	for (int i = 0; i < 10; i++)
	{
		glm::vec3 pos(200.0f + (i + 1) * (g_baseEnemySize.x + 30.0f), 200.0f, 0.0f);
		m_enemies.emplace_back(GameModule::Enemy(pos, g_baseEnemySize,
			System::ResourceManager::getInstance().getTexture("enemy_base")));
	}
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
	while (m_isRunning && m_player->isAlive())
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		float dt = currentFrame - previousFrame;
		previousFrame = currentFrame;
		m_window->clearScreen();

		render();

		for (auto& enemy : m_enemies)
		{
			enemy.update(dt, static_cast<float>(m_window->getWidth()), static_cast<float>(m_window->getHeight()),
				s_cameraView, dynamic_cast<const GameModule::GameObj&>(*m_player));
		}
	
		processCollisions();

		m_window->update();

		processInput(dt);
	}
}

void Game::render()
{
	m_player->draw(System::ResourceManager::getInstance().getShader("base_obj"), *m_renderer, s_cameraView);
	m_player->drawProjectiles(System::ResourceManager::getInstance().getShader("base_proj"), *m_renderer, s_cameraView);

	for (auto& enemy : m_enemies)
	{
		enemy.draw(System::ResourceManager::getInstance().getShader("base_obj"), *m_renderer, s_cameraView);
		enemy.drawProjectiles(System::ResourceManager::getInstance().getShader("base_proj"), *m_renderer, s_cameraView);
	}
}

void Game::processInput(float dt)
{
	float da = 0.0f;
	GameModule::MoveDir moveDir = GameModule::MoveDir::None;
	if (m_keys[GLFW_KEY_A])
	{
		da = -g_deltaAngle;
	}
	if (m_keys[GLFW_KEY_D])
	{
		da = g_deltaAngle;
	}
	if (m_keys[GLFW_KEY_W])
	{
		moveDir = GameModule::MoveDir::Up;
	}
	if (m_keys[GLFW_KEY_S])
	{
		moveDir = GameModule::MoveDir::Bottom;
	}
	m_player->update(dt, da, 
		static_cast<float>(m_window->getWidth()), static_cast<float>(m_window->getHeight()),
		s_cameraView, moveDir);

	// NOTE: This solution is not final
	if (m_keys[GLFW_MOUSE_BUTTON_LEFT])
	{
		m_player->shoot();
		m_keys[GLFW_MOUSE_BUTTON_LEFT] = false;
	}
}

void Game::processCollisions()
{
	for (auto& enemy : m_enemies)
	{
		int damage = enemy.checkProjPlayerCoollision(dynamic_cast<const GameModule::GameObj&>(*m_player));

		m_player->checkProjEnemyCoollision(enemy);
		m_player->takeDamage(damage);
	}

	m_enemies.erase(
		std::remove_if(
			m_enemies.begin(),
			m_enemies.end(),
			[](const GameModule::Enemy& enemy) {
				if (enemy.isAlive())
				{
					return false;
				}
				return true;
			}),
		m_enemies.end());
}
