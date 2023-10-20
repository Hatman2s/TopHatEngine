#pragma once

#include "THPrecomp.h"
#include "Handler.h"
#include "Events/Events.h"

namespace TopHat
{
	struct WindowProperties
	{
		std::string Title;
		unsigned int Width, Height;

		WindowProperties(const std::string& title = "TopHatEngine", 
						 unsigned int width = 1280,
						 unsigned int height = 720)
			: Title(title), Width(width), Height(height){}

	};
	class TOP_HAT_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {};

		virtual void OnUpdate() = 0;
		
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void OnEventCallback(const EventCallbackFn& eventCall) = 0;

		virtual void SetVsync(bool enabled) = 0;
		virtual bool IsVsync() const = 0;

		static Window* Create(const WindowProperties& windowProps = WindowProperties());
	};
}