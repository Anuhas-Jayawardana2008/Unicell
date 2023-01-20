#include "graphics/shader.h"

namespace unicell
{
	Shader::Shader(const std::string& path)
	{
		this->id = glCreateProgram();
		this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
		this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		
		this->ReadFile(path);

		glAttachShader(this->id, this->vertexShader);
		glAttachShader(this->id, this->fragmentShader);
		glLinkProgram(this->id);
		glValidateProgram(this->id);

		glDeleteShader(this->vertexShader);
		glDeleteShader(this->fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(this->id);
	}


	int Shader::getUniformLocation(const std::string& uniform)
	{
		int location = glGetUniformLocation(this->id, uniform.c_str());
		if (location == -1)
			std::cout << "[OpenGL Error] : Cannot find uniform ->" << uniform << std::endl;
		return location;
	}

	void Shader::setMat4(const std::string& name, const glm::mat4& value)
	{
		glUniformMatrix4fv(this->getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}
	void Shader::setVec4(const std::string& name, const glm::vec4& value)
	{
		glUniform4f(this->getUniformLocation(name), value.x, value.y, value.z, value.a);
	}

	void Shader::CompileShader(unsigned int shader, const std::string& type)
	{
		int result;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			int logLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
			char* buffer = (char*)std::calloc(logLength, sizeof(char));
			glGetShaderInfoLog(shader, logLength, &logLength, buffer);
			std::cout << "[OpenGL Error] : Failed to compile " + type + " shader" << std::endl;
			std::cout << buffer << std::endl;
			std::free(buffer);
		}
	}

	void Shader::ReadFile(const std::string& path)
	{
		enum class ShaderType
		{
			Vertex,Fragment
		};

		ShaderType current = ShaderType::Vertex;
		std::fstream stream(path);

		if (!stream)
			std::cout << "[OpenGL Error] : Failed to load " + path << std::endl;

		std::string vertex_source, fragment_source;
		std::string line;
		
		while (std::getline(stream, line))
		{
			if (line == "// vertex") current = ShaderType::Vertex;
			if (line == "// fragment") current = ShaderType::Fragment;
		
			if (current == ShaderType::Vertex) vertex_source += line + "\n";
			if (current == ShaderType::Fragment) fragment_source += line + "\n";
		}

		const char* vert = vertex_source.c_str();
		const char* frag = fragment_source.c_str();

		glShaderSource(this->vertexShader, 1, &vert, nullptr);
		glCompileShader(this->vertexShader);
		glShaderSource(this->fragmentShader, 1, &frag, nullptr);
		glCompileShader(this->fragmentShader);

		this->CompileShader(this->vertexShader, "Vertex");
		this->CompileShader(this->fragmentShader, "Fragment");
	}

	void Shader::Bind()
	{
		glUseProgram(this->id);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}
}