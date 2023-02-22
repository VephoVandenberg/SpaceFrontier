#pragma once

namespace GAME_NAMESPACE
{
	namespace GameScene
	{
		enum class Scenes 
		{
			ShutDown,
			MenuScene,
			Level1Scene
		};

		class Scene
		{
		public:
			virtual void update(float dt, const glm::vec3& cameraView) = 0;
			virtual void processInput(float dt, glm::vec3& cameraView, const glm::vec3& cursorPos, bool* const keys) = 0;
			
			inline virtual Scenes nextScene() = 0;
			inline virtual Scenes getScene() = 0;

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

			Scenes m_nextScene;
		};
	}
}
