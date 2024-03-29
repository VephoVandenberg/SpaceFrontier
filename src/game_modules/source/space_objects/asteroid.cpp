#include "../../include/player.h"
#include "../../include/space_objects/asteroid.h"

using namespace GAME_NAMESPACE::GameModule;

constexpr float g_velocityCoeff = 250.0f;
constexpr float g_deltaAngle = 30.0f;

constexpr float g_mediumAsteroidMagnitude = 160.0f;
constexpr float g_largeAsteroidMagnitude = 220.0f;
constexpr float g_hugeAsteroidMagnitude = 280.0f;

std::map<const AsteroidType, const unsigned int> Asteroid::s_asteroidSizes = {
	{AsteroidType::Medium, g_mediumAsteroidMagnitude},
	{AsteroidType::Large, g_largeAsteroidMagnitude},
	{AsteroidType::FuckinHuge, g_hugeAsteroidMagnitude}
};

Asteroid::Asteroid(glm::vec3 pos, System::Texture& texture, AsteroidType type)
	: GameObj(pos, glm::vec3(1.0f))
	, m_texture(texture)
{
	m_asteroidInfo.m_type = type;
	switch (type)
	{
	case AsteroidType::Medium:
	{
		m_scale = glm::vec3(
			glm::vec2(s_asteroidSizes[AsteroidType::Medium]),
			0.0f);
	}break;

	case AsteroidType::Large:
	{
		m_scale = glm::vec3(
			glm::vec2(s_asteroidSizes[type]),
			0.0f);
	}break;

	case AsteroidType::FuckinHuge:
	{
		m_scale = glm::vec3(
			glm::vec2(s_asteroidSizes[type]),
			0.0f);
	}break;
	}
}

void Asteroid::update(
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
		if (checkCollision(enemy))
		{
			enemy.takeDamage(m_damage);
		}
	}

	m_angle += g_deltaAngle * dt;
}

bool Asteroid::isOut(float left, float right, float bottom, float up) const
{
	bool isOutX =
		m_pos.x - m_scale.y >= right ||
		m_pos.y - m_scale.y >= up;
	bool isOutY =
		m_pos.x + m_scale.y <= left ||
		m_pos.y + m_scale.y <= bottom;
	return isOutX || isOutY;
}

void Asteroid::draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos)
{
	renderer.draw(m_angle, m_pos, m_scale, cameraPos, shader, m_texture);
}
