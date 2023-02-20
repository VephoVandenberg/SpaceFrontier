#pragma once

namespace GAME_NAMESPACE
{
	namespace GameState
	{
		class State
		{
		public:

			virtual void update() = 0;
			virtual State& nextState() const = 0;

			State() = default;
			virtual ~State() = default;
			State(State&&) = default;
			State& operator=(State&&) = default;

			State(const State&) = delete;
			State& operator=(const State&) = delete;

		private:
		};
	}
}
