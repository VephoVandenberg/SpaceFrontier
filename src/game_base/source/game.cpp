#include <time.h>
#include <functional>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../system/include/resource_manager.h"

#include "../../scenes/include/menu_scene.h"
#include "../../scenes/include/level1.h"

#include "../include/game.h"

using namespace GAME_NAMESPACE;


constexpr glm::vec3 g_playerShipSize = { 80.0f, 80.0f, 0.0f };
constexpr glm::vec3 g_baseEnemySize = { 80.0f, 80.0f, 0.0f };

glm::vec3 s_cameraView = glm::vec3(0.0f);
glm::vec3 s_cursorPos = glm::vec3(0.0f);


Game::Game()
	: m_isRunning(true)
{
	init();
}

void Game::init()
{
	srand(time(NULL));

	System::CallbackData data;
	data.func = std::bind(&Game::onEvent, this, std::placeholders::_1);

	m_window = std::unique_ptr<System::Window>(new System::Window(data));
	m_renderer = std::unique_ptr<System::Renderer>(new System::Renderer);
	
	initShaders();
	initTextures();

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_window->getWidth()),
		static_cast<float>(m_window->getHeight()), 0.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	auto playerPos = glm::vec3(m_window->getWidth() / 2.0f, m_window->getHeight() / 2.0f, 0.0f);

	m_player = std::unique_ptr<GameModule::Player>(new GameModule::Player(playerPos, g_playerShipSize,
		System::ResourceManager::getInstance().getTexture("player")));

	m_scene = std::unique_ptr<GameScene::Menu>(new GameScene::Menu(
		static_cast<float>(m_window->getWidth()), static_cast<float>(m_window->getHeight()), *m_renderer));

	System::ResourceManager::getInstance().getShader("base_obj").use();
	System::ResourceManager::getInstance().getShader("base_obj").setMatrix("uProjection", projection);
	System::ResourceManager::getInstance().getShader("base_obj").setMatrix("uView", view);
	System::ResourceManager::getInstance().getShader("base_obj").unbind();

	System::ResourceManager::getInstance().getShader("base_proj").use();
	System::ResourceManager::getInstance().getShader("base_proj").setMatrix("uProjection", projection);
	System::ResourceManager::getInstance().getShader("base_proj").setMatrix("uView", view);
	System::ResourceManager::getInstance().getShader("base_proj").unbind();

	System::ResourceManager::getInstance().getShader("base_button").use();
	System::ResourceManager::getInstance().getShader("base_button").setMatrix("uProjection", projection);
	System::ResourceManager::getInstance().getShader("base_button").setMatrix("uView", view);
	System::ResourceManager::getInstance().getShader("base_button").unbind();

	System::ResourceManager::getInstance().getShader("panel_obj").use();
	System::ResourceManager::getInstance().getShader("panel_obj").setMatrix("uProjection", projection);
	System::ResourceManager::getInstance().getShader("panel_obj").setMatrix("uView", view);
	System::ResourceManager::getInstance().getShader("panel_obj").unbind();
}

void Game::onEvent(System::Event& event)
{
	switch (event.getType())
	{
	case System::EventType::CLOSE:
	{
		m_isRunning = false;
	}break;

	case System::EventType::MOUSE_MOVE:
	{
		s_cursorPos = dynamic_cast<System::MouseMoveEvent&>(event).position;
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

void Game::initShaders()
{
	System::ResourceManager::getInstance()
		.setShader("base_obj", "shaders/base_obj_shader.vert", "shaders/base_obj_shader.frag");
	System::ResourceManager::getInstance()
		.setShader("base_proj", "shaders/base_proj_shader.vert", "shaders/base_proj_shader.frag");
	System::ResourceManager::getInstance()
		.setShader("base_button", "shaders/button_shader.vert", "shaders/button_shader.frag");
	System::ResourceManager::getInstance()
		.setShader("panel_obj", "shaders/panel_shader.vert", "shaders/panel_shader.frag");
}

void Game::initTextures()
{
	System::ResourceManager::getInstance()
		.setTexture("player", "textures/player_ship.png");
	System::ResourceManager::getInstance()
		.setTexture("enemy_base", "textures/enemy_ship.png");
	System::ResourceManager::getInstance()
		.setTexture("start_button", "textures/start_button.png");
	System::ResourceManager::getInstance()
		.setTexture("exit_button", "textures/exit_button.png");
	System::ResourceManager::getInstance()
		.setTexture("asteroid_huge_minerals", "textures/asteroid_huge_minerals.png");
	System::ResourceManager::getInstance()
		.setTexture("asteroid_huge", "textures/asteroid_huge.png");
	System::ResourceManager::getInstance()
		.setTexture("asteroid_large_minerals", "textures/asteroid_large_minerals.png");
	System::ResourceManager::getInstance()
		.setTexture("asteroid_large", "textures/asteroid_large.png");
	System::ResourceManager::getInstance()
		.setTexture("asteroid_medium_minerals", "textures/asteroid_medium_minerals.png");
	System::ResourceManager::getInstance()
		.setTexture("asteroid_medium", "textures/asteroid_medium.png");
	System::ResourceManager::getInstance()
		.setTexture("asteroid_small", "textures/asteroid_small.png");
}

void Game::run()
{
	float previousFrame = 0.0f;
	while (m_isRunning)
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		float dt = currentFrame - previousFrame;
		previousFrame = currentFrame;

		m_window->clearScreen();

		if (m_scene->nextScene() != m_scene->getScene())
		{
			switchScene();
		}
		m_scene->processInput(dt, s_cameraView, s_cursorPos, m_keys);
		m_scene->update(dt, s_cameraView);

		m_window->update();
	}
}

void Game::switchScene()
{
	// Next scene must be decided
	switch (m_scene->nextScene())
	{
	case GameScene::Scenes::Level1Scene:
		m_scene = std::unique_ptr<GameScene::Level1>(new GameScene::Level1(
			static_cast<float>(m_window->getWidth()), static_cast<float>(m_window->getHeight()), *m_player, *m_renderer));
		break;

	case GameScene::Scenes::MenuScene:
		s_cameraView = glm::vec3(0.0f);
		m_scene = std::unique_ptr<GameScene::Menu>(new GameScene::Menu(
			static_cast<float>(m_window->getWidth()), static_cast<float>(m_window->getHeight()), *m_renderer));
		break;

	case GameScene::Scenes::ShutDown:
		m_isRunning = false;
		break;
	}
}
