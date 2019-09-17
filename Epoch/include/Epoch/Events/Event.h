#pragma once

#include "pch.h"
#include "Epoch/Core.h"

namespace Epoch {

	enum class EventType
	{
		None = 0,
		WindowClosed, WindowResized, WindowMoved, WindowFocused, WindowLostFocused,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4),
	};

#define EVENT_CLASS_TYPE(type)				static EventType getStaticType() { return EventType::##type; }\
											virtual EventType getEventType() const override { return getStaticType(); }\
											virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)		virtual int getCategoryFlags() const override { return category; }

	class EGE_API Event
	{
	public:
		bool Handled = false;

		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isInCategory(EventCategory category) { return getCategoryFlags() & category; }
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e) : m_Event(e) { }

		template<typename T, typename F>
		bool dispatch(const F& function)
		{
			if (m_Event.getEventType() == T::getStaticType())
			{
				m_Event.Handled = function(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& stream, const Event& e)
	{
		return stream << e.toString();
	}

}