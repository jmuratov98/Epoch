#include "pch.h"
#include "Epoch/Application.h"

#include "Epoch/Graphics/Renderer.h"

#include "Epoch/Engine.h"

// Temporary
#include <GLFW/glfw3.h>

namespace Epoch {

	Application* Application::cm_Singleton = nullptr;

	Application::Application()
	{
		Engine::init();

		EGE_CORE_ASSERT(!cm_Singleton, "Application already exists");
		cm_Singleton = this;

		m_Window = std::unique_ptr<Window>(Window::create());
		m_Window->setEventCallback(EGE_BIND_EVENT_FN(Application::onEvent));

		Renderer::init();

		m_ImGuiLayer = new ImGuiLayer();
		pushOverLay(m_ImGuiLayer);
	}

	void Application::run()
	{
		while (m_IsRunning)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
				layer->onUpdate(timestep);

			m_ImGuiLayer->begin();
			for (Layer* layer : m_LayerStack)
				layer->onImGuiRender();
			m_ImGuiLayer->end();
			
			m_Window->onUpdate();
		}
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowClosedEvent>(EGE_BIND_EVENT_FN(Application::onWindowClosed));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->onEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::pushLayer(Layer* layer)
	{
		m_LayerStack.pushLayer(layer);
	}

	void Application::pushOverLay(Layer* overlay)
	{
		m_LayerStack.pushOverlay(overlay);
	}

	bool Application::onWindowClosed(WindowClosedEvent& e)
	{
		m_IsRunning = false;
		return true;
	}

}