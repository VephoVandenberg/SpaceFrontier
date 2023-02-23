#pragma once

#include "../../include/UI/Button.h"

using namespace GAME_NAMESPACE::GameScene;

Button::Button(glm::vec3 pos, glm::vec3 scale, glm::vec3 color)
	: GameObj(pos, scale, color)
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
		m_color.x = 0.0f;
		m_color.z = 0.0f;
	}
}
