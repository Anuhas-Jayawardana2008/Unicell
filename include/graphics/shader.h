#pragma once

#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace unicell
{
	class Shader
	{
	public:
		Shader(const std::string& path);
		~Shader();

		int getUniformLocation(const std::string& uniform);

		void setMat4(const std::string& name, const glm::mat4& value);
		void setVec4(const std::string& name, const glm::vec4& value);

		void Bind();
		void Unbind();
	private:
		void CompileShader(unsigned int shader, const std::string& type);
		void ReadFile(const std::string& path);
	private:
		unsigned int vertexShader;
		unsigned int fragmentShader;
		unsigned int id;
	};
}