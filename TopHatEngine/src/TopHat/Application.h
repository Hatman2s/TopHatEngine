#pragma once
#include "Handler.h"
#include "Events/Events.h"
namespace TopHat
{
	class TOP_HAT_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	Application* CreateGame();
}

