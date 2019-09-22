#include "pch.h"
#include "Epoch/Graphics/Shader.h"

#include "Epoch/Graphics/Renderer.h"

#include "Epoch/Platform/OpenGL/OpenGLShader.h"

namespace Epoch {

	Epoch::Shader* Shader::create(const std::string& filepath)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:		EGE_CORE_ASSERT(false, "None is not yet supported"); return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLShader(filepath);
		default:							EGE_CORE_ASSERT(false, "Unknown Render API"); return nullptr;
		}

	}

	Epoch::Shader* Shader::create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:		EGE_CORE_ASSERT(false, "None is not yet supported"); return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLShader(vertexSrc, fragmentSrc);
		default:							EGE_CORE_ASSERT(false, "Unknown Render API"); return nullptr;
		}

	}

}