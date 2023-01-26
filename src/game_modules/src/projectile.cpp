#include "../include/projectile.h"

using namespace GAME_NAMESPACE::GameModule;

constexpr float g_projVelocity = 1.5f;

Projectile::Projectile(glm::vec3 pos, glm::vec3 scale, glm::vec3 color, glm::vec3 shipVelocity, float angle)
	: GameObj(scale, pos, angle)
	, m_additionalVelocity(shipVelocity / 2.0f)
	, m_velocity(0.0f, 0.0f, 0.0f)
{
	m_velocity.x = glm::sin(m_angle) * g_projVelocity;
	m_velocity.y = -glm::cos(m_angle) * g_projVelocity;
}

void Projectile::update()
{
	m_pos += m_additionalVelocity + m_velocity;
}

bool Projectile::isOut(float borderX, float borderY) const
{
	if (m_pos.x - m_scale.y >= borderX ||
		m_pos.y - m_scale.y >= borderY ||
		m_pos.x + m_scale.y <= 0.0f ||
		m_pos.y + m_scale.y <= 0.0f)
	{
		return true;
	}
	return false;
}