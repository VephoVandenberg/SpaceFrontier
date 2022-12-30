#pragma once

#include "../../scenes/include/Scene.h"

namespace GAME_NAMESPACE
{
	namespace State
	{
		class State
		{
		public:
			State() = default;
			~State() = default;

			virtual void play() = 0;
			virtual void nextState() = 0;
		private:

		};
	}
}