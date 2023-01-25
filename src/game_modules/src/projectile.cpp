#include "../include/projectile.h"

using namespace GAME_NAMESPACE::GameModule;

constexpr float g_projVelocity = 10.0f;

Projectile::Projectile(glm::vec3 pos, glm::vec3 scale, glm::vec3 color, glm::vec3 shipVelocity, float angle)
	: GameObj(scale, pos, angle)
	, m_additionalVelocity(shipVelocity)
{
	m_velocity.x = glm::sin(m_angle) * 0.0001f;
	m_velocity.y = -glm::cos(m_angle) * 0.0001f;
}

void Projectile::update(float dt)
{
	m_pos += m_velocity;
}