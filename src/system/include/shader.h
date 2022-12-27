#pragma once

#include <string>

namespace GAME_NAMESPACE
{
	class Shader
	{
	public:
		Shader(const char* vPath, const char* fPath);
		~Shader() = default;

		void use();

		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;

		Shader() = delete;
		Shader(const Shader&) = delete;
		Shader(const Shader&&) = delete;
		Shader& operator=(const Shader&) = delete;
		Shader& operator=(const Shader&&) = delete;

	private:
		unsigned int ID;
	};
}
