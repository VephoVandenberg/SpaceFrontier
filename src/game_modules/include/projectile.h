#pragma once

#include <glm/glm.hpp>

#include "../../system/include/shader.h"

#include "game_object.h"

namespace GAME_NAMESPACE
{
	namespace GameModule
	{
		class Projectile : public GameObj
		{
		public:
			Projectile(glm::vec3 pos, glm::vec3 scale, glm::vec3 color, glm::vec3 velocitiy, glm::vec3 cameraPos, float angle);

			void update();
			bool isOut(float left, float right, float bottom, float up) const;
			void draw(System::Shader& shader, System::Renderer& renderer, const glm::vec3& cameraPos, bool hasTexture = true);

			Projectile() = default;
			~Projectile() = default;
			Projectile(const Projectile&) = default;
			Projectile(Projectile&&) = default;
			Projectile& operator=(const Projectile&) = default;
			Projectile& operator=(Projectile&&) = default;

		private:
			glm::vec3 m_velocity = { 0.0f, 0.0f, 0.0f };
			glm::vec3 m_additionalVelocity = { 0.0f, 0.0f, 0.0f };
		};
	}
}
