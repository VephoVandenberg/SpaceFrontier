#include "../../include/player.h"
#include "../../include/space_objects/meteorite.h"

using namespace GAME_NAMESPACE::GameModule;

constexpr float g_velocityCoeff = 250.0f;
constexpr float g_deltaAngle = 30.0f;

Meteorite::Meteorite(glm::vec3 pos, glm::vec3 scale, System::Texture& texture, MeteoriteType type)
	: SpaceObj(pos, scale, texture)
	, m_meteoriteInfo(type)
{}

void Meteorite::update(
	float dt,
	Player& player, std::vector<Enemy>& enemies,
	const glm::vec3& cameraPos)
{
	if (checkCollision(player))
	{
		player.takeDamage(m_damage);
	}

	for (auto& enemy : enemies)
	{
		if (checkCollision(player))
		{
			enemy.takeDamage(m_damage);
		}
	}

	m_angle += g_deltaAngle * dt;
	m_pos += m_velocity * dt;
}
