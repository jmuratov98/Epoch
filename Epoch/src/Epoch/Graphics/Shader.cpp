#include "pch.h"
#include "Epoch/Graphics/Shader.h"

#include "Epoch/Graphics/Renderer.h"

#include "Epoch/Platform/OpenGL/OpenGLShader.h"

namespace Epoch {

	Ref<Shader> Shader::create(const std::string& filepath)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:		EGE_CORE_ASSERT(false, "None is not yet supported"); return nullptr;
		case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLShader>(filepath);
		default:							EGE_CORE_ASSERT(false, "Unknown Render API"); return nullptr;
		}

	}

	Ref<Shader> Shader::create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:		EGE_CORE_ASSERT(false, "None is not yet supported"); return nullptr;
		case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		default:							EGE_CORE_ASSERT(false, "Unknown Render API"); return nullptr;
		}

	}

	void ShaderLibrary::add(const std::string& name, const Ref<Shader>& shader)
	{
		EGE_CORE_ASSERT(!exisits(name), "Shader already exists");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::add(const Ref<Shader>& shader)
	{
		auto& name = shader->getName();
		add(name, shader);
	}

	Ref<Shader> ShaderLibrary::load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::create(filepath);
		add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::load(const std::string& filepath)
	{
		auto shader = Shader::create(filepath);
		add(shader);
		return shader;
	}

	Epoch::Ref<Epoch::Shader> ShaderLibrary::get(const std::string& name)
	{
		EGE_CORE_ASSERT(exisits(name), "Shader does not exist");
		return m_Shaders[name];
	}

	bool ShaderLibrary::exisits(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}