#pragma once

#include "../../../game_modules/include/game_object.h"

namespace GAME_NAMESPACE
{
	namespace GameScene
	{
		class Button : public GameModule::GameObj
		{
		public:
			Button(glm::vec3 pos, glm::vec3 scale, glm::vec3 color);

			Button() = default;
			~Button() = default;
			Button(const Button&) = default;
			Button& operator=(const Button&) = default;
			Button(Button&&) = default;
			Button& operator=(Button&&) = default;

		private:
		};
	}
}