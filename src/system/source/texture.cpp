#include <iostream>
#include <glad/glad.h>

#include "../include/texture.h"
#include "../include/image_loader/stb_image.h"

using namespace GAME_NAMESPACE::System;

Texture::Texture(const char* tPath) 
	: ID(0)
{
	// stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(tPath, &m_width, &m_height, &m_nrChannels, 0);

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR::TEXTURE::FAILED_TO_LOAD" << std::endl;
		exit(EXIT_FAILURE);
	}

	stbi_image_free(data);
}

Texture::Texture(Texture&& texture)
	: m_width(texture.m_width)
	, m_height(texture.m_height)
	, m_nrChannels(texture.m_nrChannels)
{
	ID = texture.ID;
	texture.ID = 0;
}

Texture& Texture::operator=(Texture&& texture)
{
	if (ID == texture.ID)
	{
		return *this;
	}

	ID = texture.ID;
	texture.ID = 0;

	return *this;
}

Texture::~Texture()
{
	glDeleteTextures(1, &ID);
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ID);
}
