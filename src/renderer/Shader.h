#pragma once

#include "glm/glm.hpp"
#include "VertexBuffer.h"
#include <string>
#include <unordered_map>

namespace Vivid
{
	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string PixelSource;
	};

	class Shader
	{
	private:
		std::string m_FilePathVS;
		std::string m_FilePathPS;
		unsigned int m_RendererID;
		std::unordered_map<std::string, int> m_UniformLocationCache;

	public:
		Shader(const std::string& filepathVertexShader, const std::string& filepathPixelShader);
		~Shader();

		static Ref<Shader> Create(const std::string& filepathVertexShader, const std::string& filepathPixelShader);

		void Bind() const;

		void Unbind() const;

		// Set uniforms
		void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);

		void SetUniform4f(const std::string& name, const glm::vec4& matrix);

		void SetUniform3f(const std::string& name, float f0, float f1, float f2);

		void SetUniform3f(const std::string& name, Vec3& value);

		void SetUniform1f(const std::string& name, float value);

		void SetUniform1i(const std::string& name, int value);

		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

	private:
		int GetUniformLocation(const std::string& name);

		struct ShaderProgramSource
		ParseShader(const std::string& filepathVertexShader, const std::string& filepathPixelShader);

		unsigned int CompileShader(unsigned int type, const std::string& source);

		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	};
}