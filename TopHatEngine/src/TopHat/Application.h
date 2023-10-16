#pragma once
#include "Handler.h"
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

