#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "shader.h"
#include "texture.h"

namespace GAME_NAMESPACE
{
	namespace System
	{
		class ResourceManager
		{
		public:
			static ResourceManager& getInstance();

			~ResourceManager() = default;

			void setShader(const char* sName, const char* vPath, const char* fPath);
			Shader& getShader(const char* sName) const;

			void setTexture(const char* tName);
			Texture& getTexture(const char* tName) const;

			ResourceManager(const ResourceManager&) = delete;
			ResourceManager(const ResourceManager&&) = delete;
			ResourceManager& operator=(const ResourceManager&) = delete;
			ResourceManager&& operator=(const ResourceManager&&) = delete;
		private:
			ResourceManager() = default;

			static std::unique_ptr<ResourceManager> m_instance;
			static std::unordered_map<const char*, Shader> m_shaders;
			static std::unordered_map<const char*, Texture> m_textures;
		};
	}
}
