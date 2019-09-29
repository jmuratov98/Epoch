#pragma once

#include "pch.h"

#include "Epoch/Core.h"
#include "Epoch/Events/Event.h"

namespace Epoch {

	struct WindowProperties
	{
		unsigned int Width, Height;
		std::string Title;
		bool VSync;

		WindowProperties(unsigned int width = 1280, unsigned int height = 720, const std::string & title = "Epoch Graphics Engine", bool vsync = true)
			: Width(width), Height(height), Title(title), VSync(vsync)
		{ }
	};

	class EGE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void onUpdate() = 0;

		// Getters
		inline virtual unsigned int getWidth() const = 0;
		inline virtual unsigned int getHeight() const = 0;
		inline virtual bool isVSync() const = 0;

		inline virtual void* getNativeWindow() const = 0;

		// Setters
		virtual void setEventCallback(const EventCallbackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;

		static Window* create(const WindowProperties& props = WindowProperties());
	};

}