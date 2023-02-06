#include "../include/player.h"

using namespace GAME_NAMESPACE::GameModule;

constexpr unsigned int g_fullMag = 64;
constexpr glm::vec3 g_projSize = { 2.0f, 15.0f, 0.0f };

Player::Player(glm::vec3 pos, glm::vec3 scale, System::Texture& texture)
	: GameObj(pos, scale, texture)
	, m_acceleration(0.5f)
{}

void Player::update(float dt, float angle, float borderX, float borderY, glm::vec3& cameraPos, MoveDir dir)
{
	// Position update
	m_angle += angle * 0.5f;

	if (dir == MoveDir::Up)
	{
		m_velocity.x = glm::sin(m_angle) * m_acceleration;
		m_velocity.y = -glm::cos(m_angle) * m_acceleration;
	}
	else if (dir == MoveDir::Bottom)
	{
		m_velocity.x = -glm::sin(m_angle) * m_acceleration;
		m_velocity.y = glm::cos(m_angle) * m_acceleration;
	}
	m_pos += m_velocity;
	cameraPos += m_velocity;
	m_velocity *= 0.995f;

	// Projectile update
	for (auto& proj : m_projectiles)
	{
		proj.update();
	}

	if (!m_projectiles.empty() && m_projectiles.back().isOut(cameraPos.x, cameraPos.x + borderX, cameraPos.y, cameraPos.y + borderY))
	{
		m_projectiles.pop_front();
	}
}

void Player::shoot(const glm::vec3& cameraPos)
{
	glm::vec3 projPos = glm::vec3(m_pos.x + m_scale.x/2.0f, m_pos.y + m_scale.y/3.0f, 0.0f);
	m_projectiles.push_back(Projectile(projPos, g_projSize, m_color, m_velocity, cameraPos, m_angle));
}

void Player::draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos, bool hasTexture)
{
	if (hasTexture)
	{
		renderer.draw(m_angle, m_pos, m_scale, cameraPos, shader, m_texture);
	}

}

void Player::drawProjectiles(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos)
{
	for (auto& proj : m_projectiles)
	{
		proj.draw(shader, renderer, cameraPos, false);
	}
}

void Player::checkProjEnemyCoollision(Enemy& enemy)
{
	m_projectiles.erase(
		std::remove_if(
			m_projectiles.begin(),
			m_projectiles.end(),
			[&](const Projectile& proj) {
				if (proj.checkCollision(enemy))
				{
					enemy.takeDamage();
					return true;
				}
				return false;
			}),
		m_projectiles.end()
		);
}
