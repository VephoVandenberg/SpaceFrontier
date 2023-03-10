#include "../include/projectile.h"

using namespace GAME_NAMESPACE::GameModule;

constexpr float g_projVelocityCoeff = 750.0f;

Projectile::Projectile(glm::vec3 pos, glm::vec3 scale, glm::vec3 color, glm::vec3 shipVelocity, float angle)
	: GameObj(pos, scale, color, angle)
	, m_additionalVelocity(shipVelocity / 12.0f)
	, m_velocity(0.0f, 0.0f, 0.0f)
{
	m_velocity.x = glm::sin(glm::radians(m_angle)) * g_projVelocityCoeff;
	m_velocity.y = -glm::cos(glm::radians(m_angle)) * g_projVelocityCoeff;
}

void Projectile::update(float dt)
{
	m_pos += (m_velocity + m_additionalVelocity) * dt;
}

bool Projectile::isOut(float left, float right, float bottom, float up) const
{
	bool isOutX =
		m_pos.x - m_scale.y >= right ||
		m_pos.y - m_scale.y >= up;
	bool isOutY =
		m_pos.x + m_scale.y <= left ||
		m_pos.y + m_scale.y <= bottom;
	return isOutX || isOutY;
}
 