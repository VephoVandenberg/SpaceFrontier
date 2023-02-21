#include "../../system/include/resource_manager.h"
#include "../include/level1.h"

using namespace GAME_NAMESPACE::GameScene;

constexpr glm::vec3 g_baseEnemySize = { 80.0f, 80.0f, 0.0f };

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
	for (int i = 0; i < 10; i++)
	{
		glm::vec3 pos(200.0f + (i + 1) * (g_baseEnemySize.x + 30.0f), 200.0f, 0.0f);
		m_enemies.emplace_back(GameModule::Enemy(pos, g_baseEnemySize,
			System::ResourceManager::getInstance().getTexture("enemy_base")));
	}
}

void Level1::onDetatch()
{

}

void Level1::update(float dt, const glm::vec3& cameraView)
{
	for (auto& enemy : m_enemies)
	{
		enemy.update(dt, m_width, m_height, cameraView, dynamic_cast<const GameModule::GameObj&>(m_player));

		int damage = enemy.checkProjPlayerCoollision(dynamic_cast<const GameModule::GameObj&>(m_player));
		m_player.checkProjEnemyCoollision(enemy);
		m_player.takeDamage(damage);
	}

	processCollisions();

	render(cameraView);
}

void Level1::render(const glm::vec3& cameraView)
{
	m_player.draw(System::ResourceManager::getInstance().getShader("base_obj"), m_renderer, cameraView);
	m_player.drawProjectiles(System::ResourceManager::getInstance().getShader("base_proj"), m_renderer, cameraView);

	for (auto& enemy : m_enemies)
	{
		enemy.draw(System::ResourceManager::getInstance().getShader("base_obj"), m_renderer, cameraView);
		enemy.drawProjectiles(System::ResourceManager::getInstance().getShader("base_proj"), m_renderer, cameraView);
	}
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

Scene* Level1::nextState()
{
	return nullptr;
}
