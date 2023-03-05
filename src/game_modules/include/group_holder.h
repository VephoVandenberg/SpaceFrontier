#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "../include/game_object.h"

namespace GAME_NAMESPACE
{
	namespace GameModule
	{
		namespace DataStructures
		{
			class GroupHolder
			{
			public:
				GroupHolder(glm::vec3 pos, float width, float height);

				void push_back(GameObj* element);
				void setObjects();

				GameObj* operator[](unsigned int index);

				GroupHolder() = default;
				~GroupHolder() = default;

				GroupHolder(const GroupHolder&) = delete;
				GroupHolder& operator=(const GroupHolder&) = delete;
				GroupHolder(GroupHolder&&) = delete;
				GroupHolder& operator=(GroupHolder&&) = default;

			private:
				glm::vec3 m_pos;
				float m_width = 0;
				float m_height = 0;

				std::vector<GameObj*> m_objects;
			};
		}
	}
}
