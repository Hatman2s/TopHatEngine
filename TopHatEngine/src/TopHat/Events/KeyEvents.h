#pragma once

#include "Events.h"

//precompiled headers coming soon
 

namespace TopHat
{

	class  KeyEvent: public Event
	{
	public:

		inline int GetKeyCode() { return m_KeyCode; }

		EVENT_CATAGORY(EventCatagoryInput | EventCatagoryKeyboard)

	protected:

		KeyEvent(int keyCode):m_KeyCode(keyCode){}
		int m_KeyCode;
	};

	class   KeyDownEvent: public KeyEvent
	{
	public:
		
		KeyDownEvent(int keyCode, int repeatCount): KeyEvent(keyCode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << " Key Down Event! KeyCode: " << m_KeyCode << " Repeats: " << m_RepeatCount << " times";
			return ss.str();
		}

		EVENT_TYPE(KeyDown)

	private:
		int m_RepeatCount;
	};
	class  KeyUpEvent : public KeyEvent
	{
	public:

		KeyUpEvent(int keyCode) : KeyEvent(keyCode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << " Key Up Event! KeyCode: " << m_KeyCode;
			return ss.str();
		}

		EVENT_TYPE(KeyUp)

	};



}
