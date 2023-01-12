#include "Shader.h"
#include "Renderer.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Shader::Shader(const std::string& filepathVertexShader, const std::string& filepathPixelShader)
    : m_FilePathVS(filepathVertexShader)
    , m_FilePathPS(filepathPixelShader)
    , m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepathVertexShader, filepathPixelShader);

	m_RendererID = CreateShader(source.VertexSource, source.PixelSource);

	GLCall(glUseProgram(m_RendererID));
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "No active uniform variable with name " << name << " found" << std::endl;

	m_UniformLocationCache[name] = location;

	return location;
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform3f(const std::string& name, Vec3& value)
{
	GLCall(glUniform3f(GetUniformLocation(name), (GLfloat)value.x, (GLfloat)value.y, (GLfloat)value.z));
}

void Shader::SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
{
	GLCall(glUniform4f(GetUniformLocation(name), f0, f1, f2, f3));
}

void Shader::SetUniform4f(const std::string& name, const glm::vec4& matrix)
{
	GLCall(glUniform4f(GetUniformLocation(name), matrix.x, matrix.y, matrix.z, matrix.w));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

enum ShaderType
{
	NONE = -1,
	VERTEX = 0,
	PIXEL = 1
};

struct ShaderProgramSource
Shader::ParseShader(const std::string& filepathVertexShader, const std::string& filepathPixelShader)
{
	std::ifstream streamVS(filepathVertexShader);
	std::ifstream streamPS(filepathPixelShader);
	std::string line;
	std::stringstream ss[2];
	ShaderType type = NONE;

	while (getline(streamVS, line))
	{
		ss[VERTEX] << line << '\n';
	}
	while (getline(streamPS, line))
	{
		ss[PIXEL] << line << '\n';
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	GLCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	// Error handling
	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "pixel") << " shader compile status: " << result << std::endl;
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout
		    << "Failed to compile "
		    << (type == GL_VERTEX_SHADER ? "vertex" : "pixel")
		    << "shader"
		    << std::endl;
		std::cout << message << std::endl;
		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& pixelShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int ps = CompileShader(GL_FRAGMENT_SHADER, pixelShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, ps));

	GLCall(glLinkProgram(program));

	GLint program_linked;

	GLCall(glGetProgramiv(program, GL_LINK_STATUS, &program_linked));
	std::cout << "Program link status: " << program_linked << std::endl;
	if (program_linked != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		GLCall(glGetProgramInfoLog(program, 1024, &log_length, message));
		std::cout << "Failed to link program" << std::endl;
		std::cout << message << std::endl;
	}

	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(ps));

	return program;
}