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

			virtual void update(
				float dt, 
				Player& player,std::vector<Enemy>& enemies,
				const glm::vec3& cameraPos) = 0;
			void draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos) override;

			SpaceObj() = default;
			virtual ~SpaceObj() = default;
			SpaceObj(SpaceObj&&) = default;
			SpaceObj& operator=(SpaceObj&&) = default;

			SpaceObj(const SpaceObj&) = delete;
			SpaceObj& operator=(const SpaceObj&) = delete;

		protected:
			unsigned int m_damage = 30;

			System::Texture& m_texture;
		};
	}
}
