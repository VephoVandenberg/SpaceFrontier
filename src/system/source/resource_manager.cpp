#include <iostream>

#include "../include/resource_manager.h"

using namespace GAME_NAMESPACE::System;

std::unordered_map<const char*, Shader> ResourceManager::m_shaders;
std::unique_ptr<ResourceManager> ResourceManager::m_instance = nullptr;

ResourceManager& ResourceManager::getInstance()
{
	if (!m_instance)
	{
		m_instance = std::unique_ptr<ResourceManager>(new ResourceManager);
	}
	return *m_instance;
}

void ResourceManager::setShader(const char* shaderName, const char* vPath, const char* fPath)
{
	Shader shader(vPath, fPath);
	m_shaders[shaderName] = shader;
}

Shader& ResourceManager::getShader(const char* shaderName) const
{
	if (m_shaders.find(shaderName) == m_shaders.end())
	{
		std::cout << "ERROR::RESOURCE_MANAGER::NO_SUCH_KEY" << std::endl;
		exit(EXIT_FAILURE);
	}
	return m_shaders[shaderName];
}
