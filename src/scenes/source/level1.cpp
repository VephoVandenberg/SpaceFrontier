#include <time.h>
#include <glfw3.h>

#include "../../system/include/resource_manager.h"

#include "../include/level1.h"

using namespace GAME_NAMESPACE::GameScene;

constexpr glm::vec3 g_baseEnemySize = { 80.0f, 80.0f, 0.0f };
constexpr float g_deltaAngle = 75.0f;
constexpr float g_groupWidth = 400.0f;
constexpr float g_groupHeight = 700.0f;
constexpr float g_meteorBorderAddition = 140.0f;
constexpr float g_distanceToKeep = 40.0f;
constexpr unsigned int g_enemiesInOneGroup = 5;

Level1::Level1(float width, float height, GameModule::Player& player, System::Renderer& renderer)
	: m_width(width)
	, m_height(height)
	, m_timer(0.0f)
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
	glm::vec3 initialEnemyGroupPos = glm::vec3(500.0f, 200.0f, 0.0f);
	// Init groups
	for (auto& group : m_enemyGroups)
	{
		srand(time(nullptr));
		group = GameModule::DataStructures::GroupHolder(initialEnemyGroupPos, g_distanceToKeep, g_groupWidth, g_groupHeight);
	}

	// Init Enemies
	m_player.reset(glm::vec3(m_width / 2.0f, m_height / 2.0f, 0.0f));

	for (unsigned int i = 0, groupIndex = 0; i < g_enemyGroupNumber * g_enemiesInOneGroup; i++)
	{
		m_enemies.emplace_back(GameModule::Enemy(glm::vec3(0.0f), g_baseEnemySize,
			System::ResourceManager::getInstance().getTexture("enemy_base")));
	}

	for (auto& enemy : m_enemies)
	{
		m_enemyGroups[0].push_back(&enemy);
	}

	m_enemyGroups[0].setObjects();

	m_nextScene = Scenes::Level1Scene;
}

void Level1::onDetatch()
{

}

void Level1::update(float dt, const glm::vec3& cameraView)
{
	processCollisions();

	// Handle meteorite spawn and update
	if (!m_spaceObjects.empty())
	{
		for (auto& spaceObj : m_spaceObjects)
		{
			spaceObj.update(dt, m_player, m_enemies, cameraView);
			spaceObj.draw(
				System::ResourceManager::getInstance().getShader("base_obj"),
				m_renderer, cameraView);
		}

		if (m_spaceObjects.back().isOut(
			cameraView.x, cameraView.x + m_width,
			cameraView.y, cameraView.y + m_height))
		{
			m_spaceObjects.pop_front();
		}
	}
	else
	{
		spawnMeteorite(cameraView);
	}

	// Handle enemies
	for (unsigned int i = 0;
		i < m_enemies.size();
		i++)
	{
		// Update enemies
		m_enemies[i].update(dt, m_width, m_height, m_player, cameraView, m_enemies, m_spaceObjects);
		renderEnemy(m_enemies[i], cameraView);
		if (enemyOutOfBorder(m_enemies[i], cameraView))
		{
			m_enemies[i].drawMarker(
				System::ResourceManager::getInstance().getShader("panel_obj"),
				m_renderer, cameraView);
		}
	}

	if (!m_player.isAlive() || m_enemies.empty())
	{
		m_nextScene = Scenes::MenuScene;
	}


	render(cameraView);
}

bool Level1::enemyOutOfBorder(const GameModule::Enemy& enemy, const glm::vec3& cameraView)
{
	bool isOutX =
		0.0f > enemy.getPos().x - enemy.getScale().x - cameraView.x ||
		m_width < enemy.getPos().x - cameraView.x;
	bool isOutY =
		0.0f > enemy.getPos().y - enemy.getScale().y - cameraView.y ||
		m_height < enemy.getPos().y - cameraView.y;
	return isOutX || isOutY;
}

void Level1::render(const glm::vec3& cameraView)
{
	m_player.draw(
		System::ResourceManager::getInstance().getShader("base_obj"),
		m_renderer, cameraView);
	m_player.drawProjectiles(
		System::ResourceManager::getInstance().getShader("base_proj"),
		m_renderer, cameraView);
}

void Level1::renderEnemy(GameModule::Enemy& enemy, const glm::vec3& cameraView)
{
	enemy.draw(
		System::ResourceManager::getInstance().getShader("base_obj"),
		m_renderer, cameraView);
	enemy.drawProjectiles(
		System::ResourceManager::getInstance().getShader("base_proj"),
		m_renderer, cameraView);
}

void Level1::spawnMeteorite(const glm::vec3& cameraView)
{
	srand(time(nullptr));
	float partX = rand() % 2 + 1;
	float partY = rand() % 2 + 1;

	glm::vec3 orienatation = {
		(partX == 1) ? 1 : -1,
		(partY == 1) ? 1 : -1,
		0.0f
	};

	float posX =
		(partX == 1) ? cameraView.x - 100.0f : cameraView.x + m_width + 100.0f;
	float posY = 
		(partY == 1) ? cameraView.y - 100.0f : cameraView.y + m_height + 100.0f;

	glm::vec3 pos = {posX, posY, 0.0f };

	unsigned int type = rand() % 2 + 1;
	GameModule::MeteoriteType meteorType = static_cast<GameModule::MeteoriteType>(type);
	switch (meteorType)
	{
	case GameModule::MeteoriteType::Small:
	{
		m_spaceObjects.emplace_back(
			GameModule::Meteorite(pos, orienatation,
				System::ResourceManager::getInstance().getTexture("meteorite_small"),
				meteorType));
	}break;

	case GameModule::MeteoriteType::Medium:
	{
		m_spaceObjects.emplace_back(
			GameModule::Meteorite(pos, orienatation,
				System::ResourceManager::getInstance().getTexture("meteorite_medium"),
				meteorType));
	}break;
	}
}

void Level1::processCollisions()
{
	m_enemies.erase(
		std::remove_if(
			m_enemies.begin(),
			m_enemies.end(),
			[&](const GameModule::Enemy& enemy) {
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
