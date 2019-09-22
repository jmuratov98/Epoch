#pragma once

#include "Epoch/Window.h"

#include "Epoch/Graphics/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Epoch {
	
	class WindowsWindow : public Window
	{
	public: // Public Functions
		WindowsWindow(const WindowProperties& props);
		virtual ~WindowsWindow();

		virtual void onUpdate() override;

		// Getters
		inline virtual unsigned int getWidth() const override { return m_Data.Width; }
		inline virtual unsigned int getHeight() const override { return m_Data.Height; }
		inline virtual bool isVSync() const override { return m_Data.VSync; }
		
		inline virtual void* getNativeWindow() const override { return m_Window; }

		// Setters
		virtual void setEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		virtual void setVSync(bool enabled) override;

	private: // Private Functions
		void init(const WindowProperties& props);
		void shutdown();

	private: // Private Member Variables
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

	private:
		struct WindowsData
		{
			unsigned int Width, Height;
			std::string Title;
			bool VSync;

			EventCallbackFn EventCallback;
		} m_Data;

	};

}