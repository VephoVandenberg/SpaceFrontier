#pragma once

#include <string>
#include <glm/glm.hpp>

namespace GAME_NAMESPACE
{
	namespace System
	{
		class Shader
		{
		public:
			Shader(const char* vPath, const char* fPath);
			~Shader();
			Shader() = default;
			Shader& operator=(const Shader&) = default;

			void use() const;
			void unbind() const;

			void setBool(const std::string& name, bool value) const;
			void setInt(const std::string& name, int value) const;
			void setFloat(const std::string& name, float value) const;
			void setMatrix(const std::string& name, glm::mat4& matrix) const;
			void setVector3f(const std::string& name, glm::vec3& vector) const;

			Shader(const Shader&) = delete;
			Shader(const Shader&&) = delete; 
			Shader& operator=(const Shader&&) = delete;

		private:
			unsigned int ID;
		};
	}
}
