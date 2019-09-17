#pragma once

#include "Epoch/Core.h"

#include "Epoch/Window.h"
#include "Epoch/Graphics/Layers/LayerStack.h"
#include "Epoch/Events/Event.h"
#include "Epoch/Events/ApplicationEvents.h"

namespace Epoch {

	class EGE_API Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void run();

		void onEvent(Event& e);

		void pushLayer(Layer* layer);
		void pushOverLay(Layer* overlay);

		inline static Application& get() { return *cm_Singleton; }

	private:
		bool onWindowClosed(WindowClosedEvent& e);

	private:
		bool m_IsRunning = true;

		std::unique_ptr<Window> m_Window;

		LayerStack m_LayerStack;
	
	private:
		static Application* cm_Singleton;
	};

	Application* create_application();

}