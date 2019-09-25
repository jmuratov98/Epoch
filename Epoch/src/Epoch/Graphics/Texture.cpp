#include "pch.h"
#include "Epoch/Graphics/Texture.h"

#include "Epoch/Graphics/Renderer.h"
#include "Epoch/Platform/OpenGL/OpenGLTexture.h"

namespace Epoch {

	Ref<Texture2D> Texture2D::create(const std::string& filepath)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:		EGE_CORE_ASSERT(false, "None is not yet supported"); return nullptr;
		case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLTexture2D>(filepath);
		default:							EGE_CORE_ASSERT(false, "Unknown Render API"); return nullptr;
		}
	}

}