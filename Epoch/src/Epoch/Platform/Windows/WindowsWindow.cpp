#include "pch.h"
#include "Epoch/Platform/Windows/WindowsWindow.h"

#include "Epoch/Events/ApplicationEvents.h"
#include "Epoch/Events/MouseEvents.h"
#include "Epoch/Events/KeyEvents.h"

#include "Epoch/Platform/OpenGL/OpenGLGraphicsContext.h"

namespace Epoch {

	static bool is_glfw_init = false;

	void error_callback(int code, const char* description)
	{
		EGE_CORE_ERROR("GLFW Error ({0}): {1}", code, description);
	}

	Window* Window::create(const WindowProperties& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		shutdown();
	}

	void WindowsWindow::init(const WindowProperties& props)
	{
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.Title = props.Title;

		EGE_CORE_INFO("Creating window {0}, ({1}, {2})", props.Title, props.Width, props.Height);

		if (!is_glfw_init)
		{
			int success = glfwInit();
			EGE_CORE_ASSERT(success, "Could not initialize GLFW");
			glfwSetErrorCallback(error_callback);
			is_glfw_init = true;
		}

		m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);

		m_Context = new OpenGLGraphicsContext(m_Window);
		m_Context->init();
		
		glfwSetWindowUserPointer(m_Window, &m_Data);
		setVSync(true);

		// Setting GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizedEvent e(width, height);
			data.EventCallback(e);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);
			WindowClosedEvent e;
			data.EventCallback(e);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int keycode, int scancode, int action, int mods)
		{
			WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent e(keycode, 0);
					data.EventCallback(e);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent e(keycode, 1);
					data.EventCallback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent e(keycode);
					data.EventCallback(e);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent e(keycode);
			data.EventCallback(e);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent e(button);
					data.EventCallback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent e(button);
					data.EventCallback(e);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double x, double y)
		{
			WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent e((float)x, (float)y);
			data.EventCallback(e);
		});
		
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
		{
			WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent e((float)x, (float)y);
			data.EventCallback(e);
		});
	}

	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::onUpdate()
	{
		glfwPollEvents();
		m_Context->swapBuffers();
	}

	void WindowsWindow::setVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapBuffers(0);
		m_Data.VSync = enabled;
	}

}