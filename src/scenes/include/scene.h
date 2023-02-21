#pragma once

namespace GAME_NAMESPACE
{
	namespace GameScene
	{
		class Scene
		{
		public:
			virtual void update(float dt, const glm::vec3& cameraView) = 0;
			virtual Scene* nextState() = 0;

			Scene() = default;
			virtual ~Scene() = default;
			Scene(Scene&&) = default;
			Scene& operator=(Scene&&) = default;

			Scene(const Scene&) = delete;
			Scene& operator=(const Scene&) = delete;

		protected:
			virtual void onAttach() = 0;
			virtual void onDetatch() = 0;
			virtual void render(const glm::vec3& cameraView) = 0;
		};
	}
}
