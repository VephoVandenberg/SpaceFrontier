#include "../include/player.h"

using namespace GAME_NAMESPACE::GameModule;

constexpr unsigned int g_fullMag = 64;
constexpr float g_borderAddition = 400.0f;
constexpr glm::vec3 g_projSize = { 2.0f, 15.0f, 0.0f };

Player::Player(glm::vec3 pos, glm::vec3 scale, System::Texture& texture)
	: GameObj(pos, scale)
	, m_texture(texture)
	, m_velocityCoeff(400.0f)
{}

void Player::update(float dt, float da, float borderX, float borderY, glm::vec3& cameraPos, MoveDir dir)
{
	// Position update
	m_angle += da * dt;

	if (dir == MoveDir::Up)
	{
		m_velocity.x = glm::sin(m_angle) * m_velocityCoeff;
		m_velocity.y = -glm::cos(m_angle) * m_velocityCoeff;
	}
	else if (dir == MoveDir::Bottom)
	{
		m_angle -= 2.0f * da * dt;
		m_velocity.x = -glm::sin(m_angle) * m_velocityCoeff;
		m_velocity.y = glm::cos(m_angle) * m_velocityCoeff;
	}
	m_pos += m_velocity * dt;
	cameraPos += m_velocity * dt;
	m_velocity *= 0.995f;

	// Projectile update
	for (auto& proj : m_projectiles)
	{
		proj.update(dt);
	}

	if (!m_projectiles.empty() && 
		m_projectiles.back().isOut(
			cameraPos.x - g_borderAddition, cameraPos.x + borderX + g_borderAddition, 
			cameraPos.y - g_borderAddition, cameraPos.y + borderY + g_borderAddition))
	{
		m_projectiles.pop_front();
	}
}

void Player::shoot()
{
	glm::vec3 projPos = glm::vec3(m_pos.x + m_scale.x/2.0f, m_pos.y + m_scale.y/3.0f, 0.0f);
	m_projectiles.push_back(Projectile(projPos, g_projSize, m_color, m_velocity, m_angle));
}

void Player::draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos)
{
	renderer.draw(m_angle, m_pos, m_scale, cameraPos, shader, m_texture);
}

void Player::drawProjectiles(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos)
{
	for (auto& proj : m_projectiles)
	{
		proj.draw(shader, renderer, cameraPos);
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
