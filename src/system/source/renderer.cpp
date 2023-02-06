#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

#include "../include/renderer.h"

using namespace GAME_NAMESPACE::System;

Renderer::Renderer()
{
	init();
}

void Renderer::init()
{
	float vertices[] = {
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f
	};


	unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3
	};

	unsigned int VBO, EBO;

	glGenVertexArrays(1, &m_quadVAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(m_quadVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Renderer::draw(float angle, glm::vec3& pos, glm::vec3& scale, Shader& shader)
{
	shader.use();

	glm::mat4 model = glm::translate(glm::mat4(1.0f), pos);

	model = glm::translate(model, scale / 2.0f);
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, -scale / 2.0f);

	model = glm::scale(model, scale);
	shader.setMatrix("uModel", model);
	
	glBindVertexArray(m_quadVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::draw(float angle, glm::vec3& pos, glm::vec3& scale, const glm::vec3& viewDir, Shader& shader)
{
	shader.use();

	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, pos);

	model = glm::translate(model, scale / 2.0f);
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, -scale / 2.0f);

	model = glm::scale(model, scale);
	shader.setMatrix("uModel", model);

	glm::mat4 view = glm::translate(glm::mat4(1.0f), -viewDir);
	shader.setMatrix("uView", view);

	glBindVertexArray(m_quadVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void Renderer::draw(float angle, glm::vec3& pos, glm::vec3& scale, Shader& shader, Texture& texture)
{
	shader.use();

	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, pos);

	model = glm::translate(model, scale / 2.0f);
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, -scale / 2.0f);

	model = glm::scale(model, scale);
	shader.setMatrix("uModel", model);

	shader.setInt("uTexture", 0);
	texture.bind();
	glBindVertexArray(m_quadVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void Renderer::draw(float angle, glm::vec3& pos, glm::vec3& scale, const glm::vec3& viewDir, Shader& shader, Texture& texture)
{
	shader.use();

	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, pos);

	model = glm::translate(model, scale / 2.0f);
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, -scale / 2.0f);

	model = glm::scale(model, scale);
	shader.setMatrix("uModel", model);

	glm::mat4 view = glm::translate(glm::mat4(1.0f), -viewDir);
	shader.setMatrix("uView", view);

	shader.setInt("uTexture", 0);
	texture.bind();
	glBindVertexArray(m_quadVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
