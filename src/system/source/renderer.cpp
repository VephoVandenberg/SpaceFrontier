#include <glad/glad.h>

#include "../include/renderer.h"

namespace GAME_NAMESPACE
{
	Renderer::Renderer()
	{
		init();
	}

	void Renderer::init()
	{
		float vertices[] = {
			0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f
		};

		float indices[] = {
			0, 1, 2,
			1, 2, 3
		};
	
		unsigned int VBO, EBO;
		
		glGenVertexArrays(1, &m_quadVAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(m_quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
	}

	void Renderer::draw(Shader& shader)
	{
		shader.use();
		glBindVertexArray(m_quadVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}