#pragma once

#include "Epoch/Graphics/GraphicsContext.h"

struct GLFWwindow;

namespace Epoch {

	class OpenGLGraphicsContext : public GraphicsContext
	{
	public:
		OpenGLGraphicsContext(GLFWwindow* window_handler);
		
		virtual void init() override;
		virtual void swapBuffers() override;

	private:
		GLFWwindow* m_Handler;
	};

}