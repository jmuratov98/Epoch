#pragma once

#include "Epoch/Graphics/Shader.h"

#include <glm/glm.hpp>

namespace Epoch {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual const std::string& getName() const override { return m_Name; }

		void uploadUniformInt(const std::string& name, int value);

		void uploadUniformFloat(const std::string& name, float value);
		void uploadUniformFloat2(const std::string& name, const glm::vec2& vector);
		void uploadUniformFloat3(const std::string& name, const glm::vec3& vector);
		void uploadUniformFloat4(const std::string& name, const glm::vec4& vector);

		void uploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void uploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		std::string readFile(const std::string& filepath);
		std::unordered_map<unsigned int, std::string> preProcess(const std::string& source);
		void compile(const std::unordered_map<unsigned int, std::string>& shaderSources);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};

}