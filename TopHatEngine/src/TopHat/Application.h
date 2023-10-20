#pragma once
#include "Handler.h"
#include "Events/Events.h"
#include "Window.h"
namespace TopHat
{
	class TOP_HAT_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();	
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	Application* CreateGame();
}

