#include "pch.h"
#include "Epoch/Graphics/RendererCommand.h"

#include "Epoch/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Epoch {

	RendererAPI* RendererCommand::cm_RendererAPI = new OpenGLRendererAPI;

}