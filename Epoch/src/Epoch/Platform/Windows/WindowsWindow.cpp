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
		m_Data.Title = props.Title;
		m_Data.VSync = props.VSync;
		m_Data.Mode = props.Mode;
		m_Data.IsMaximized = false;
		m_Data.WindowWidth = props.Width;
		m_Data.WindowHeight= props.Height;

		if (!is_glfw_init)
		{
			// TODO: Add glfwTerminate();
			int success = glfwInit();
			EGE_CORE_ASSERT(success, "Could not initialize GLFW");
			glfwSetErrorCallback(error_callback);
			is_glfw_init = true;
		}

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* videomode = glfwGetVideoMode(monitor);

		switch(m_Data.Mode)
		{
		case WINDOW:
			m_Data.Width = props.Width;
			m_Data.Height = props.Height;
			break;
		case FULL_SCREEN: case BORDERLESS:
			m_Data.Width = videomode->width;
			m_Data.Height = videomode->height;
			break;
		default:
			m_Data.Width = props.Width;
			m_Data.Height = props.Height;
			break;
			
		}

		glfwWindowHint(GLFW_DECORATED, m_Data.Mode == WindowMode::WINDOW ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, m_Data.Mode == WindowMode::WINDOW ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_FLOATING, m_Data.Mode == WindowMode::FULL_SCREEN ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_AUTO_ICONIFY, m_Data.Mode == WindowMode::FULL_SCREEN ? GLFW_TRUE : GLFW_FALSE);
		EGE_CORE_INFO("Creating window {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);
		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);

		if (m_Data.Mode == WindowMode::WINDOW)
			glfwGetWindowPos(m_Window, &m_Data.WindowPosition.x, &m_Data.WindowPosition.y);
		else if (m_Data.Mode == WindowMode::BORDERLESS)
			glfwMaximizeWindow(m_Window);

		m_Context = create_scope<OpenGLGraphicsContext>(m_Window);
		m_Context->init();

		setVSync(m_Data.VSync);

		// Setting GLFW callbacks
		glfwSetWindowUserPointer(m_Window, &m_Data);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
			if (data.Mode == WindowMode::WINDOW && !data.IsMaximized)
			{
				data.WindowWidth = width;
				data.WindowHeight = height;
			}

			WindowResizedEvent e(width, height);
			data.EventCallback(e);
		});

		glfwSetWindowMaximizeCallback(m_Window, [](GLFWwindow* window, int maximized)
		{
			WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);

			if (data.Mode == WindowMode::WINDOW)
				data.IsMaximized = maximized == GLFW_TRUE ? true : false;
		});

		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int posX, int posY)
		{
			WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);
			if (data.Mode == WindowMode::WINDOW)
				data.WindowPosition = { posX, posY };
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

	void WindowsWindow::setWindowMode(const WindowMode& mode)
	{
		EGE_CORE_ASSERT(m_Window, "Window is not created");
		if (mode == m_Data.Mode) return;

		GLFWmonitor* windowRenderScreen = glfwGetPrimaryMonitor(); // where the window will be rendered
		const GLFWvidmode* baseVideoMode = glfwGetVideoMode(windowRenderScreen);

		// Disable callbacks temporarily, to prevent multiple resize events firing during this scope
		auto resizeCallbackFn = glfwSetWindowSizeCallback(m_Window, NULL);
		auto moveCallbackFn = glfwSetWindowPosCallback(m_Window, NULL);
		auto maximizeCallbackFn = glfwSetWindowMaximizeCallback(m_Window, NULL);

		glm::i32vec2 oldPos, newPos;
		glfwGetWindowPos(m_Window, &oldPos.x, &oldPos.y);

		switch (m_Data.Mode)
		{
		case WindowMode::BORDERLESS:
			glfwRestoreWindow(m_Window);
			break;
		case WindowMode::FULL_SCREEN:
			break;
		case WindowMode::WINDOW:
			if (m_Data.IsMaximized)
			{
				glfwRestoreWindow(m_Window);
				glfwGetWindowPos(m_Window, &newPos.x, &newPos.y);
				m_Data.WindowPosition = newPos;
			}
			break;
		}

		int width, height;
		switch (mode)
		{
		case WindowMode::BORDERLESS:
			width = baseVideoMode->width;
			height = baseVideoMode->height;
			break;
		case WindowMode::FULL_SCREEN:
			width = baseVideoMode->width;
			height = baseVideoMode->height;
			break;
		case WindowMode::WINDOW:
			width = m_Data.WindowWidth;
			height = m_Data.WindowHeight;
			break;
		}

		EGE_CORE_ASSERT(m_Window, "Failed to retrieve window.");
		m_Data.Mode = mode;
		glfwSetWindowAttrib(m_Window, GLFW_DECORATED, m_Data.Mode == WindowMode::WINDOW ? GLFW_TRUE : GLFW_FALSE);
		glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, m_Data.Mode == WindowMode::WINDOW ? GLFW_TRUE : GLFW_FALSE);
		glfwSetWindowAttrib(m_Window, GLFW_FLOATING, m_Data.Mode == WindowMode::FULL_SCREEN ? GLFW_TRUE : GLFW_FALSE);
		glfwSetWindowAttrib(m_Window, GLFW_AUTO_ICONIFY, m_Data.Mode == WindowMode::FULL_SCREEN ? GLFW_TRUE : GLFW_FALSE);
		glfwSetWindowMonitor(m_Window,
			m_Data.Mode == WindowMode::FULL_SCREEN ? windowRenderScreen : nullptr,
			m_Data.Mode == WindowMode::WINDOW ? m_Data.WindowPosition.x : 0,
			m_Data.Mode == WindowMode::WINDOW ? m_Data.WindowPosition.y : 0,
			width, height,
			baseVideoMode->refreshRate);
		if (m_Data.Mode == WindowMode::BORDERLESS || (m_Data.Mode == WindowMode::WINDOW && m_Data.IsMaximized))
			glfwMaximizeWindow(m_Window);

		// re-enable callbacks
		glfwSetWindowSizeCallback(m_Window, resizeCallbackFn);
		glfwSetWindowPosCallback(m_Window, moveCallbackFn);
		glfwSetWindowMaximizeCallback(m_Window, maximizeCallbackFn);

		// manually raising a single resize event if needed (in correct order)
		glfwGetWindowPos(m_Window, &newPos.x, &newPos.y);
		if (oldPos != newPos)
			moveCallbackFn(m_Window, newPos.x, newPos.y);
		glfwGetWindowSize(m_Window, &width, &height);
		if (width != m_Data.Width || height != m_Data.Height)
			resizeCallbackFn(m_Window, width, height);

		if (glfwGetWindowAttrib(m_Window, GLFW_FLOATING) == GLFW_FALSE)
			glfwShowWindow(m_Window);
	}

}