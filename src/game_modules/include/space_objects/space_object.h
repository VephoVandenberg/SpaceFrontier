#pragma once

#include <vector>

#include "../game_object.h"

namespace GAME_NAMESPACE
{
	namespace GameModule
	{
		class System::Texture;

		class Player;
		class Enemy;

		class SpaceObj : public GameObj
		{
		public:
			SpaceObj(glm::vec3 pos, glm::vec3 scale, System::Texture& texture);

			virtual void update(float dt, float borderX, float borderY, Player& player, const glm::vec3& cameraPos, const std::vector<Enemy>& enemies);
			void draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos) override;

			SpaceObj() = default;
			virtual ~SpaceObj() = default;
			SpaceObj(SpaceObj&&) = default;
			SpaceObj& operator=(SpaceObj&&) = default;

			SpaceObj(const SpaceObj&) = delete;
			SpaceObj& operator=(const SpaceObj&) = delete;

		protected:
			unsigned int m_damage = 5;

			System::Texture& m_texture;
		};
	}
}
