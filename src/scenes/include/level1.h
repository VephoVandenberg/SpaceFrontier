#pragma once

#include <vector>

#include "../../system/include/renderer.h"

#include "../../game_modules/include/player.h"
#include "../../game_modules/include/enemies/enemy.h"

#include "scene.h"

namespace GAME_NAMESPACE
{
	namespace GameScene
	{
		class Level1 : public Scene
		{
		public:
			Level1(float width, float height, GameModule::Player& player, System::Renderer& renderer);
			~Level1();

			void update(float dt, const glm::vec3& cameraView) override;
			Scene* nextState() override;

			Level1(Level1&&) = default;
			Level1& operator=(Level1&&) = default;

			Level1() = delete;
			Level1(const Level1&) = delete;
			Level1& operator=(const Level1&) = delete;

		protected:
			void onAttach() override;
			void onDetatch() override;
			void render(const glm::vec3& cameraView) override;

		private:
			void processCollisions();

			float m_width;
			float m_height;

			System::Renderer& m_renderer;
			GameModule::Player& m_player;
			std::vector<GameModule::Enemy> m_enemies;
		};
	}
}
