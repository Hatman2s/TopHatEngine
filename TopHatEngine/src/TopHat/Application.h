#pragma once
#include "Handler.h"
#include "Events/Events.h"
#include "Events/ApplicationEvents.h"
#include "Window.h"
namespace TopHat
{
	class TOP_HAT_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();	
		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& wc);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	Application* CreateGame();
}

