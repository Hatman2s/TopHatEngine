#include "THPrecomp.h"
#include "Application.h"

#include "Events/ApplicationEvents.h"
#include "Log.h"
#include "glad/glad.h"
namespace TopHat
{
#define EVENT_BIND(x) std::bind(&Application::x, this, std::placeholders::_1)


	Application::Application()
	{

		m_Window = std::unique_ptr<Window>(Window::Create());
		TH_ENGINE_INFO("Engine Initialised");
		m_Window->OnEventCallback(EVENT_BIND(OnEvent));
	}
	Application::~Application(){}

	void Application::PushLayer(Layer* layer)
	{
		 
		ls.PushLayer(layer);
	}
	void Application::PushOverlay(Layer* layer)
	{
		ls.PushOverlay(layer);
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatch(e);
		dispatch.Dispatch<WindowCloseEvent>(EVENT_BIND(OnWindowClose));

		/*std::cout << e.ToString();*/
		/*TH_ENGINE_TRACE("{0}", e);*/
		for(auto it = ls.End(); it != ls.Begin();)
		{
			(*--it)->OnEvent(e);
			if(e.handled)
			{
				break;
			}
		}
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
			for (Layer* layer : ls.GetLayers())
				layer->OnUpdate();
			m_Window->OnUpdate();
		}
		 
	}

	bool Application::OnWindowClose(WindowCloseEvent& wc)
	{
		m_Running = false;
		return true;
	}
}