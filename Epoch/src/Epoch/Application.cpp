#include "pch.h"
#include "Epoch/Application.h"

#include "Epoch/Engine.h"

// Temporary
#include <glad/glad.h>

namespace Epoch {

	Application* Application::cm_Singleton = nullptr;

	Application::Application()
	{
		Engine::init();

		EGE_CORE_ASSERT(!cm_Singleton, "Application already exists");
		cm_Singleton = this;

		m_Window = std::unique_ptr<Window>(Window::create());
		m_Window->setEventCallback(EGE_BIND_EVENT_FN(Application::onEvent));
	}

	void Application::run()
	{
		while (m_IsRunning)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->onUpdate();

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