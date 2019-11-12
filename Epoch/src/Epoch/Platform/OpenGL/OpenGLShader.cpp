#include "pch.h"
#include "Epoch/Platform/OpenGL/OpenGLShader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

#include <fstream>

namespace Epoch {

	static GLenum shader_type_from_string(const std::string& type)
	{
		if (type == "vertex")							return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")		return GL_FRAGMENT_SHADER;
		EGE_CORE_ASSERT(false, "Unknown Shader Type");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string source = readFile(filepath);
		auto shaderSources = preProcess(source);
		compile(shaderSources);

		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		std::unordered_map<unsigned int, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}


	std::string OpenGLShader::readFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			EGE_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}

	std::unordered_map<unsigned int, std::string> OpenGLShader::preProcess(const std::string& source)
	{
		std::unordered_map<unsigned int, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLen = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			EGE_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLen + 1;
			std::string type = source.substr(begin, eol - begin);
			EGE_CORE_ASSERT(shader_type_from_string(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			EGE_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos);

			shaderSources[shader_type_from_string(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	void OpenGLShader::compile(const std::unordered_map<unsigned int, std::string>& shaderSources)
	{
		unsigned int program = glCreateProgram();
		EGE_CORE_ASSERT(shaderSources.size() <= 2, "We only support 2 shaders for now");
		std::array<unsigned int, 2> shaderIDs;

		int shaderIDIndex = 0;
		for (auto& kv : shaderSources)
		{
			unsigned int type = kv.first;
			const std::string& source = kv.second;


			unsigned int shader = glCreateShader(type);
			const char* source_c = source.c_str();
			glShaderSource(shader, 1, &source_c, 0);
			
			glCompileShader(shader);

			int isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				int maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<char> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				EGE_CORE_ERROR("{0}", infoLog.data());
				EGE_CORE_ASSERT(false, "Shader compilation failed");
				break;
			}
			
			glAttachShader(program, shader);
			shaderIDs[shaderIDIndex++] = shader;
		}

		m_RendererID = program;

		glLinkProgram(program);
		
		int isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)& isLinked);
		if (isLinked == GL_FALSE)
		{
			int maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);
			
			for (auto id : shaderIDs)
				glDeleteShader(id);

			EGE_CORE_ERROR("{0}", infoLog.data());
			EGE_CORE_ASSERT(false, "Shader linking failed");
			return;
		} 

		for (auto id : shaderIDs) {
			glDetachShader(program, id);
			glDeleteShader(id);
		}

	}

	void OpenGLShader::bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::uploadUniformInt(const std::string& name, int value)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::uploadUniformFloat(const std::string& name, float value)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::uploadUniformFloat2(const std::string& name, const glm::vec2& vector)
	{

		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, vector.x, vector.y);
	}

	void OpenGLShader::uploadUniformFloat3(const std::string& name, const glm::vec3& vector)
	{

		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void OpenGLShader::uploadUniformFloat4(const std::string& name, const glm::vec4& vector)
	{

		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

	void OpenGLShader::uploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::uploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}