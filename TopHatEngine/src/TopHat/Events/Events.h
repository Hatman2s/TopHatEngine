#pragma once

#include "TopHat/Handler.h"

//precompiled header coming soon
#include <string>
#include <functional>

namespace TopHat
{
	//current event system runs as imediate rather then deffering the event to be handled in a 
	//queue

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFullScreen, WindowWindowed, WindowMoved, 
		AppTick, AppUpdate, AppRender,
		KeyDown, KeyUp,
		MouseButtonDown, MouseButtonUp, MouseMoved, MouseScrolled
	
	};

	enum EventCatagory
	{
		None = 0,
		EventCatagoryApp = BIT(0),
		EventCatagoryInput = BIT(1),
		EventCatagoryKeyboard = BIT(2),
		EventCatagoryMouse = BIT(3),
		EventCatagoryMouseButton = BIT(4)

	};

	//fun fact: so the below lines look confusing but are actually rather clever.
	//so #define we know is used to define macros which in turn can be used as a QOL 
	//tool to developers. below is what is defined as a multi-lined function macro.
	//here in the macro we take in an input type for an event and distribute it through
	//the decleration of each of the functions.(the backslash signifies a new line).
	//a couple explenations: "##" is used as a merging operator that merges the input 
	//and a declared type. don't ask me how that works i don't know so ill be using it
	//sparingly. a single "#" turns a variable name into a string which is why its present
	//in the get name function :)

	#define EVENT_TYPE(type) static EventType GetStaticType(){return EventType::##type;}\
							 virtual EventType GetType() const override{return GetStaticType();}\
							 virtual const char* GetName() const override {return #type;}

	#define EVENT_CATAGORY(catagory) virtual int GetCatagoryFlags() const override {return catagory;}


	//fun fact: const = 0 at the end of a function signifies its purely virtual
	//thus meaning the class its from is an abstract class requiring the function
	//to be definied by children of the class;
	class TOP_HAT_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCatagoryFlags() const = 0;
		virtual std::string ToString() const = 0;

		inline bool IsEventCatagory(EventCatagory e)
		{
			return GetCatagoryFlags() & e;
		}
	protected:
		bool m_Handled = false;
	};

	class TOP_HAT_API EventDispatcher
	{
		//T must always be of Type Event 
		template <typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& e): m_Event(e){}

		//T must always be of Type Event 
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if(m_Event.GetType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator << (std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}