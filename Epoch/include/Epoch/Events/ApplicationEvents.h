#pragma once

#include "Epoch/Events/Event.h"

namespace Epoch {

	class EGE_API WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent() { }

		EVENT_CLASS_TYPE(WindowClosed)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class EGE_API WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) { }

		inline unsigned int getWidth() const { return m_Width; }
		inline unsigned int getHeight() const { return m_Height; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowResizedEvent: ( " << m_Width << ", " << m_Height << " )";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResized)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_Width, m_Height;
	};

	class EGE_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() { }

		EVENT_CLASS_TYPE(AppTick)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class EGE_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() { }

		EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class EGE_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() { }

		EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

}