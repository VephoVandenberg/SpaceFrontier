#include "../include/group_holder.h"

using namespace GAME_NAMESPACE::GameModule;
using namespace GAME_NAMESPACE::GameModule::DataStructures;

constexpr unsigned int g_initNumber = 16;

GroupHolder::GroupHolder(glm::vec3 pos, float width, float height)
	: m_pos(pos)
	, m_width(width)
	, m_height(height)
{}

void GroupHolder::push_back(GameObj* element)
{
	m_objects.push_back(element);
}

GameObj* GroupHolder::operator[](unsigned int index)
{
	return m_objects[index];
}

void GroupHolder::setObjects()
{
	int x = 0;
	int y = 0;
	for (unsigned int i = 0; i < m_objects.size(); i++)
	{
		glm::vec3 newPos = {
			m_pos.x + x * (m_objects[i]->getScale().x + 30.0f),
			m_pos.y + y * (m_objects[i]->getScale().y + 30.0f),
			0.0f };

		m_objects[i]->setPos(newPos);

		if (newPos.x - m_width >= m_width)
		{
			x = 0;
			y++;
		}
		else
		{
			x++;
		}
	}
}
