#pragma once

#include "Epoch/Core/Core.h"

#include "Epoch/Core/Window.h"

#include "Epoch/Graphics/Layers/LayerStack.h"
#include "Epoch/Graphics/Layers/ImGuiLayer.h"

#include "Epoch/Core/Timestep.h"

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

		inline Window& getWindow() { return *m_Window; }
		inline static Application& get() { return *cm_Singleton; }
	private:
		bool onWindowClosed(WindowClosedEvent& e);
		bool onWindowResized(WindowResizedEvent& e);

	private:
		bool m_IsRunning = true;
		bool m_IsMinimized = false;
		float m_LastFrameTime = 0.0f;

		LayerStack m_LayerStack;

		ImGuiLayer* m_ImGuiLayer;
		std::unique_ptr<Window> m_Window;

	private:
		static Application* cm_Singleton;
	};

	Application* create_application();

}