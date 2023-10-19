#pragma once

#include "Events.h"

//precompiled headers coming soon
#include <sstream>

namespace TopHat
{
	class TOP_HAT_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y): m_MouseX(x), m_MouseY(y){}

		inline float GetX() { return m_MouseX; }
		inline float GetY() { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << " Mouse Moved Event! X = " << m_MouseX << " Y = " << m_MouseY;
			return ss.str();
		}
		EVENT_TYPE(MouseMoved)
		EVENT_CATAGORY(EventCatagoryMouse | EventCatagoryInput)
	protected:
		float m_MouseX, m_MouseY;
	};

	class TOP_HAT_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float x, float y) : m_XOff(x), m_YOff(y) {}

		inline float GetXOffset() { return m_XOff; }
		inline float GetYOffset() { return m_YOff; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << " Mouse Moved Event! X offset= " << m_XOff << " Y offset = " << m_YOff;
			return ss.str();
		}
		EVENT_TYPE(MouseScrolled)
			EVENT_CATAGORY(EventCatagoryMouse | EventCatagoryInput)
	protected:
		float m_XOff, m_YOff;
	};

	class TOP_HAT_API MouseButtonEvent : public Event
	{
	public:

		inline int GetButton() { return m_Button; }

		EVENT_CATAGORY(EventCatagoryInput | EventCatagoryMouse | EventCatagoryMouseButton)

	protected:

		MouseButtonEvent(int button) :m_Button(button) {}
		int m_Button;
	};

	class TOP_HAT_API MouseButtonDownEvent : public MouseButtonEvent
	{
	public:

		MouseButtonDownEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << " Mouse Button Down Event! Button: " << m_Button;
			return ss.str();
		}

		EVENT_TYPE(MouseButtonDown)
	};
	class TOP_HAT_API MouseButtonUpEvent : public MouseButtonEvent
	{
	public:

		MouseButtonUpEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << " Mouse Button Up Event! Button: " << m_Button;
			return ss.str();
		}

		EVENT_TYPE(MouseButtonUp)
	};
}