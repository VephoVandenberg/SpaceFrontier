#include "../../include/enemies/marker.h"

using namespace GAME_NAMESPACE::GameModule;

constexpr glm::vec3 g_markerScale = { 3.0f, 3.0f, 0.0f };
constexpr float g_markerPosMagnitude = 300.0f;

Marker::Marker(glm::vec3 color, float angle)
	: GameObj(glm::vec3(0.0f), g_markerScale, color, angle)
{}

void Marker::update(float dt, glm::vec3 playerPos, glm::vec3 enemyPos)
{
	glm::vec3 playerToEnemy = enemyPos - playerPos;
	m_pos = playerPos + g_markerPosMagnitude * glm::normalize(playerToEnemy);
}
