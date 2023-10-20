#include "THPrecomp.h"
#include "Application.h"

#include "Events/ApplicationEvents.h"
#include "Log.h"
#include "GLFW/glfw3.h"
namespace TopHat
{
	Application::Application()
	{
		TopHat::Log::init();
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	Application::~Application(){}

	void Application::Run()
	{
		WindowResizeEvent e(1980, 1080);
		if(e.IsEventCatagory(EventCatagoryApp))
		{
			TH_ENGINE_TRACE(e);
		}
		while(m_Running)
		{
			glClearColor(0, 0.91764705882, 1, 0);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
		while (true)
		{

		}
	}
}