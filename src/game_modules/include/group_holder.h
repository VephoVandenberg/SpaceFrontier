#pragma once

#include <vector>

#include <glm/glm.hpp>

namespace GAME_NAMESPACE
{
	namespace GameModule
	{
		namespace DataStructures
		{
			template<typename T>
			class GroupHolder
			{
			public:
				GroupHolder(glm::vec3 pos, glm::vec3 scale, float width, float height);

				void push_back(T* element);
				void setObjects();

				T& operator[](unsigned int index);

				GroupHolder() = default;
				~GroupHolder() = default;

				GroupHolder(const GroupHolder&) = delete;
				GroupHolder& operator=(const GroupHolder&) = delete;
				GroupHolder(GroupHolder&&) = delete;
				GroupHolder& operator=(GroupHolder&&) = default;

			private:
				glm::vec3 m_pos;
				glm::vec3 m_scale;
				float m_width = 0;
				float m_height = 0;

				std::vector<T*> m_objects;
			};

			template<typename T>
			GroupHolder<T>::GroupHolder(glm::vec3 pos, glm::vec3 scale, float width, float height)
				: m_pos(pos)
				, m_scale(scale)
				, m_width(width)
				, m_height(height)
			{}

			template<typename T>
			void GroupHolder<T>::push_back(T* element)
			{
				m_objects.push_back(element);
			}

			template<typename T>
			T& GroupHolder<T>::operator[](unsigned int index)
			{
				return m_objects[index];
			}

			template<typename T>
			void GroupHolder<T>::setObjects()
			{
				unsigned int x = 0;
				unsigned int y = 0;
				for (auto& obj : m_objects)
				{
					glm::vec3 newPos = {
						m_width + x * m_scale.x + 30.0f,
						m_height + y * m_scale.y + 30.0f,
						0.0f };

					if (m_scale.x * x > m_width)
					{
						x = 0;
						y++;
					}
					x++;
				}
			}
		}
	}
}
