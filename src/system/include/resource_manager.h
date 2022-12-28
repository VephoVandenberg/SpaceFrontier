#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "shader.h"

namespace GAME_NAMESPACE
{
	namespace System
	{
		class ResourceManager
		{
		public:
			static ResourceManager& getInstance();

			~ResourceManager() = default;

			void setShader(const char* shaderName, const char* vPath, const char* fPath);
			Shader& getShader(const char* shaderName) const;

			ResourceManager(const ResourceManager&) = delete;
			ResourceManager(const ResourceManager&&) = delete;
			ResourceManager& operator=(const ResourceManager&) = delete;
			ResourceManager&& operator=(const ResourceManager&&) = delete;
		private:
			ResourceManager() = default;

			static std::unique_ptr<ResourceManager> m_instance;
			static std::unordered_map<const char*, Shader> m_shaders;
		};
	}
}
