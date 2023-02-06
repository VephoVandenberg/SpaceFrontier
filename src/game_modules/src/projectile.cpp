#include "../include/projectile.h"

using namespace GAME_NAMESPACE::GameModule;

constexpr float g_projVelocity = 1.1f;

Projectile::Projectile(glm::vec3 pos, glm::vec3 scale, glm::vec3 color, glm::vec3 shipVelocity, glm::vec3 cameraPos, float angle)
	: GameObj(pos, scale, angle)
	, m_additionalVelocity(shipVelocity / 4.0f)
	, m_velocity(0.0f, 0.0f, 0.0f)
{
	m_velocity.x = glm::sin(m_angle) * g_projVelocity;
	m_velocity.y = -glm::cos(m_angle) * g_projVelocity;
}

void Projectile::update()
{
	m_pos += m_velocity + m_additionalVelocity;
}

void Projectile::draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos, bool hasTexture)
{
	renderer.draw(m_angle, m_pos, m_scale, cameraPos, shader);
}

bool Projectile::isOut(float left, float right, float bottom, float up) const
{
	if (m_pos.x - m_scale.y >= right ||
		m_pos.y - m_scale.y >= up ||
		m_pos.x + m_scale.y <= left||
		m_pos.y + m_scale.y <= bottom)
	{
		return true;
	}
	return false;
}
