#include "pch.h"
#include "Epoch/Graphics/RendererCommand.h"

#include "Epoch/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Epoch {

	Scope<RendererAPI> RendererCommand::cm_RendererAPI = create_scope<OpenGLRendererAPI>();

}