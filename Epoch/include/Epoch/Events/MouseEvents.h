#pragma once

#include "Epoch/Events/Event.h"

namespace Epoch {
	
	class EGE_API MouseButtonEvent : public Event
	{
	public:
		inline int getButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)

	protected:
		MouseButtonEvent(int button) : m_Button(button) { }

		int m_Button;
	};

	class EGE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class EGE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

	class EGE_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float x, float y) : m_X(x), m_Y(y) { }

		inline float getXScrolled() const { return m_X; }
		inline float getYScrolled() const { return m_Y; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: (" << m_X << ", " << m_Y << " )";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_X, m_Y;
	};

	class EGE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) : m_X(x), m_Y(y) { }

		inline float getXScrolled() const { return m_X; }
		inline float getYScrolled() const { return m_Y; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: (" << m_X << ", " << m_Y << " )";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_X, m_Y;
	};

}