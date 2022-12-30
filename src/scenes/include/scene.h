#pragma once

namespace GAME_NAMESPACE
{
	namespace Scene
	{
		class Scene
		{
		public:
			Scene() = default;
			~Scene() = default;

			virtual void play() = 0;
		private:
		};
	}
}