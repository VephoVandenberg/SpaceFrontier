#include <iostream>

#include "../include/resource_manager.h"

using namespace GAME_NAMESPACE::System;

std::unordered_map<const char*, Shader> ResourceManager::m_shaders;
std::unordered_map<const char*, Texture> ResourceManager::m_textures;
std::unique_ptr<ResourceManager> ResourceManager::m_instance = nullptr;

ResourceManager& ResourceManager::getInstance()
{
	if (!m_instance)
	{
		m_instance = std::unique_ptr<ResourceManager>(new ResourceManager);
	}
	return *m_instance;
}

void ResourceManager::setShader(const char* sName, const char* vPath, const char* fPath)
{
	Shader shader(vPath, fPath);
	m_shaders[sName] = shader;
}

Shader& ResourceManager::getShader(const char* sName) const
{
	if (m_shaders.find(sName) == m_shaders.end())
	{
		std::cout << "ERROR::RESOURCE_MANAGER::GET_SHADER::NO_SUCH_KEY" << std::endl;
		exit(EXIT_FAILURE);
	}
	return m_shaders[sName];
}

void ResourceManager::setTexture(const char* tName, const char *tPath)
{
	Texture texture(tPath);
	m_textures[tName] = texture;
}

Texture& ResourceManager::getTexture(const char* tName) const
{
	if (m_textures.find(tName) == m_textures.end())
	{
		std::cout << "ERROR::RESOURCE_MANAGER::GET_SHADER::NO_SUCH_KEY" << std::endl;
		exit(EXIT_FAILURE);
	}
	return m_textures[tName];
}
