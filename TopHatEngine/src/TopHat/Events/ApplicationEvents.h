#pragma once

#include "Events.h"

//precompiled headers coming soon
 

namespace TopHat
{
	
	class TOP_HAT_API WindowResizeEvent: public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height): m_Width(width), m_Height(height){}

		inline int GetWidth() { return m_Width; }
		inline int GetHeight() { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << " Window Resize Event! Width: " << m_Width << " Height: " << m_Height;
			return ss.str();
		}
		EVENT_TYPE(WindowResize)
		EVENT_CATAGORY(EventCatagoryApp)
	private:
		unsigned int m_Width, m_Height;
	};

	class TOP_HAT_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent(){}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << " Window Close Event!";
			return ss.str();
		}
		EVENT_TYPE(WindowClose)
		EVENT_CATAGORY(EventCatagoryApp)
	};
	
	class TOP_HAT_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}
		EVENT_TYPE(AppTick)
			EVENT_CATAGORY(EventCatagoryApp)
	};

	class TOP_HAT_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}
		EVENT_TYPE(AppUpdate)
			EVENT_CATAGORY(EventCatagoryApp)
	};
	class TOP_HAT_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}
		EVENT_TYPE(AppRender)
			EVENT_CATAGORY(EventCatagoryApp)
	};
	 


}
