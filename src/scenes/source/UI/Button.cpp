#pragma once

#include "../../include/UI/Button.h"

using namespace GAME_NAMESPACE::GameScene;

Button::Button(glm::vec3 pos, glm::vec3 scale, glm::vec3 color, System::Texture& texture)
	: GameObj(pos, scale, color)
	, m_texture(texture)
{

}

void Button::changeColor()
{
	if (m_isTarget)
	{
		m_color.x = 0.5f;
		m_color.z = 0.5f;
		if (m_isClicked)
		{
			m_color.x = 0.3f;
			m_color.z = 0.3f;
		}
		else
		{
			m_color.x = 0.5f;
			m_color.z = 0.5f;
		}
	}
	else
	{
		m_color.x = 1.0f;
		m_color.z = 1.0f;
	}
}

void Button::draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos)
{
	renderer.draw(m_angle, m_pos, m_scale, m_color, cameraPos, shader, m_texture);
}
