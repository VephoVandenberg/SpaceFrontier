#include <iostream>
#include <sstream>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include "../include/shader.h"

using namespace GAME_NAMESPACE::System;

Shader::Shader(const char* vPath, const char* fPath) 
	: ID(0)
{
	std::string vCode, fCode;
	std::ifstream vFile, fFile;

	vFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vFile.open(vPath);
		fFile.open(fPath);

		std::stringstream vStream, fStream;

		vStream << vFile.rdbuf();
		fStream << fFile.rdbuf();

		vFile.close();
		fFile.close();

		vCode = vStream.str();
		fCode = fStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER_FILE_NOT_READ_SUCCESFULLY" << std::endl;
	}

	const char* vSrc = vCode.c_str();
	const char* fSrc = fCode.c_str();

	unsigned int vShader, fShader;
	int success;
	char log[512];

	vShader = glCreateShader(GL_VERTEX_SHADER);
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vShader, 1, &vSrc, nullptr);
	glShaderSource(fShader, 1, &fSrc, nullptr);
	glCompileShader(vShader);
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vShader, 512, nullptr, log);
		std::cout << "SHADER::VERTEX::ERROR " << log << std::endl;
	}
	glCompileShader(fShader);
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fShader, 512, nullptr, log);
		std::cout << "SHADER::FRAGMENT::ERROR " << log << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vShader);
	glAttachShader(ID, fShader);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, nullptr, log);
		std::cout << "SHADER::LINKING::ERROR " << log << std::endl;
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	use();
}

Shader::Shader(Shader&& shader)
{
	ID = shader.ID;
	shader.ID = 0;
}

Shader& Shader::operator=(Shader&& shader)
{
	if (ID == shader.ID)
	{
		return *this;
	}

	ID = shader.ID;
	shader.ID = 0;

	return *this;
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

void Shader::use() const
{
	glUseProgram(ID);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMatrix(const std::string& name, glm::mat4& matrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setVector3f(const std::string& name, glm::vec3& vector) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(vector));
}
