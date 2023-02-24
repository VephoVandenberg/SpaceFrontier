#pragma once

#include <vector>

namespace GAME_NAMESPACE
{
	namespace GameModule
	{
		class GameObj;

		class GroupHolder
		{
		public:
		private:
			std::vector<GameObj&> m_objects;
		};
	}
}