#pragma once

#include "Epoch/Events/Event.h"

namespace Epoch {

	class EGE_API KeyEvent : public Event
	{
	public:
		inline int getKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard)

	protected:
		KeyEvent(int keycode) : m_KeyCode(keycode) { }

		int m_KeyCode;
	};

	class EGE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int count) : KeyEvent(keycode), m_Count(count) { }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " ( " << m_Count << " )";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:

		int m_Count;
	};

	class EGE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) { }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class EGE_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode) : KeyEvent(keycode) { }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

}