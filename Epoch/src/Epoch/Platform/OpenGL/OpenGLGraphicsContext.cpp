#include "pch.h"
#include "Epoch/Platform/OpenGL/OpenGLGraphicsContext.h"

#include "Epoch/Core.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Epoch {

	OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* window_handler)
		: m_Handler(window_handler)
	{
		EGE_CORE_ASSERT(window_handler, "Window handler is null");
	}

	void OpenGLGraphicsContext::init()
	{
		glfwMakeContextCurrent(m_Handler);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EGE_CORE_ASSERT(status, "Failed to initialize Glad");

		EGE_CORE_INFO("OpenGL Info:");
		EGE_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		EGE_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		EGE_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLGraphicsContext::swapBuffers()
	{
		glfwSwapBuffers(m_Handler);
	}

}