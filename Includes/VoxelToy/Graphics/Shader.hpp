#pragma once

#include "glm/glm.hpp"

namespace VoxelToy
{
	class Shader
	{
	public:
		Shader() = delete;
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader();

		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

		void Bind() const;
		[[maybe_unused]] static void UnBind() ;

		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform2f(const std::string& name, float v0, float v1);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

	private:
		int GetUniformLocation(const std::string& name);
		unsigned int CompileShader(unsigned int type, const std::string& source);

	public:
		unsigned int m_ID;
		std::string m_vertexFilePath;
		std::string m_fragmentFilePath;
		std::unordered_map<std::string, int> m_UniformLocationCache;
	};
}// namespace VoxelToy
