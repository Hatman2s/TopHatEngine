#include "THPrecomp.h"
#include "Application.h"

#include "Events/ApplicationEvents.h"
#include "Log.h"
namespace TopHat
{
	Application::Application(){}
	Application::~Application(){}

	void Application::Run()
	{
		WindowResizeEvent e(1980, 1080);
		if(e.IsEventCatagory(EventCatagoryApp))
		{
			TH_ENGINE_TRACE(e);
		}
		while (true)
		{

		}
	}
}