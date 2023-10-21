#include "THPrecomp.h"
#include "Application.h"

#include "Events/ApplicationEvents.h"
#include "Log.h"
#include "GLFW/glfw3.h"
namespace TopHat
{
#define EVENT_BIND(x) std::bind(&Application::x, this, std::placeholders::_1)


	Application::Application()
	{
		TopHat::Log::init();
		m_Window = std::unique_ptr<Window>(Window::Create());
		TH_ENGINE_INFO("Engine Initialised");
		m_Window->OnEventCallback(EVENT_BIND(OnEvent));
	}
	Application::~Application(){}


	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatch(e);
		dispatch.Dispatch<WindowCloseEvent>(EVENT_BIND(OnWindowClose));

		TH_ENGINE_TRACE("{0}", e);
	}

	

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
		 
	}

	bool Application::OnWindowClose(WindowCloseEvent& wc)
	{
		m_Running = false;
		return true;
	}
}