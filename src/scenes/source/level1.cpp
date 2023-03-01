#include <glfw3.h>

#include "../../system/include/resource_manager.h"
#include "../include/level1.h"

using namespace GAME_NAMESPACE::GameScene;

constexpr glm::vec3 g_baseEnemySize = { 80.0f, 80.0f, 0.0f };
constexpr float g_deltaAngle = 2.0f;

Level1::Level1(float width, float height, GameModule::Player& player, System::Renderer& renderer)
	: m_width(width)
	, m_height(height)
	, m_player(player)
	, m_renderer(renderer)
{
	onAttach();
}

Level1::~Level1()
{
	onDetatch();
}

void Level1::onAttach()
{
	m_player.reset(glm::vec3(m_width/2.0f, m_height/2.0f, 0.0f));
	for (int i = 0; i < 10; i++)
	{
		glm::vec3 pos(200.0f + (i + 1) * (g_baseEnemySize.x + 30.0f), 200.0f, 0.0f);
		m_enemies.emplace_back(GameModule::Enemy(pos, g_baseEnemySize,
			System::ResourceManager::getInstance().getTexture("enemy_base")));
	}
	m_nextScene = Scenes::Level1Scene;
}

void Level1::onDetatch()
{

}

void Level1::update(float dt, const glm::vec3& cameraView)
{
	processCollisions();

	for (auto& enemy : m_enemies)
	{
		enemy.update(dt, m_width, m_height, cameraView, dynamic_cast<const GameModule::GameObj&>(m_player));

		for (auto& collEnemy : m_enemies)
		{
			if (enemy != collEnemy)
			{
				enemy.checkEnemyEnemyCollision(collEnemy);
			}
		}

		int damage = enemy.checkProjPlayerCoollision(dynamic_cast<const GameModule::GameObj&>(m_player));
		m_player.checkProjEnemyCoollision(enemy);
		m_player.takeDamage(damage);

		if (!m_player.isAlive())
		{
			m_nextScene = Scenes::MenuScene;
		}

		renderEnemy(enemy, cameraView);
	}


	render(cameraView);
}

void Level1::render(const glm::vec3& cameraView)
{
	m_player.draw(System::ResourceManager::getInstance().getShader("base_obj"), m_renderer, cameraView);
	m_player.drawProjectiles(System::ResourceManager::getInstance().getShader("base_proj"), m_renderer, cameraView);

}

void Level1::renderEnemy(GameModule::Enemy& enemy, const glm::vec3& cameraView)
{
	enemy.draw(System::ResourceManager::getInstance().getShader("base_obj"), m_renderer, cameraView);
	enemy.drawProjectiles(System::ResourceManager::getInstance().getShader("base_proj"), m_renderer, cameraView);
}

void Level1::processCollisions()
{

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

void Level1::processInput(float dt, glm::vec3& cameraView, const glm::vec3& cursorPos, bool* const keys)
{
	float da = 0.0f;
	GameModule::MoveDir moveDir = GameModule::MoveDir::None;
	if (keys[GLFW_KEY_A])
	{
		da = -g_deltaAngle;
	}
	if (keys[GLFW_KEY_D])
	{
		da = g_deltaAngle;
	}
	if (keys[GLFW_KEY_W])
	{
		moveDir = GameModule::MoveDir::Up;
	}
	if (keys[GLFW_KEY_S])
	{
		moveDir = GameModule::MoveDir::Bottom;
	}
	m_player.update(dt, da, m_width, m_height, cameraView, moveDir);

	// NOTE: This solution is not final
	if (keys[GLFW_MOUSE_BUTTON_LEFT])
	{
		m_player.shoot();
		keys[GLFW_MOUSE_BUTTON_LEFT] = false;
	}
}
