#include "pch.h"
#include "Epoch/Graphics/VertexArray.h"

#include "Epoch/Graphics/Renderer.h"
#include "Epoch/Platform/OpenGL/OpenGLVertexArray.h"

namespace Epoch {

	Ref<VertexArray> VertexArray::create()
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:		EGE_CORE_ASSERT(false, "None is not yet supported"); return nullptr;
		case RendererAPI::API::OpenGL:		return create_ref<OpenGLVertexArray>();
		default:							EGE_CORE_ASSERT(false, "Unknown Render API"); return nullptr;
		}
	}

}