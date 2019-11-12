#include "pch.h"
#include "Epoch/Platform/OpenGL/OpenGLGraphicsContext.h"

#include "Epoch/Core/Core.h"

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

		#ifdef EGE_ENABLE_ASSRETS
			int version_major;
			int version_minor;
			glGetIntegerv(GL_MAJOR_VERSION, &version_major);
			glGetIntegerv(GL_MINOR_VERSION, &version_minor);
			
			EGE_CORE_ASSERT(version_major > 4 || (version_major == 4 && version_minor >= 5), "Hazel requires at least OpenGL version 4.5!");
		#endif
	}

	void OpenGLGraphicsContext::swapBuffers()
	{
		glfwSwapBuffers(m_Handler);
	}

}