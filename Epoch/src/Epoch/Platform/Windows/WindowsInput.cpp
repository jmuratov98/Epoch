#include "pch.h"
#include "Epoch/Platform/Windows/WindowsInput.h"

#include "Epoch/Application.h"

#include "GLFW/glfw3.h"

namespace Epoch {

	Input* Input::cm_Singleton = new WindowsInput();

	bool WindowsInput::isKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return (state == GLFW_PRESS || state ==	GLFW_REPEAT);
	}

	bool WindowsInput::isMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::getMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { (float)x, (float)y };
	}

	float WindowsInput::getXImpl()
	{
		auto [x, y] = getMousePosImpl();
		return x;
	}

	float WindowsInput::getYImpl()
	{
		auto [x, y] = getMousePosImpl();
		return y;
	}

}