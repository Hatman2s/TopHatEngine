#include "THPrecomp.h"
#include "Application.h"
#include "Events/ApplicationEvents.h"
#include "Log.h"
#include "glm.hpp"


#include "Renderer/Renderer.h"

namespace TopHat
{
#define EVENT_BIND(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;
	Application::Application()
	{
		TH_FRAMEWORK_ASSERTS(!s_Instance, "Application already created!")
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		TH_ENGINE_INFO("Engine Initialised");
		Renderer::Init();
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
		dispatch.Dispatch<WindowResizeEvent>(EVENT_BIND(OnWindowResize));

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
			m_DeltaT.CalculateDeltaTime();
			float dt = m_DeltaT;
			if(!m_Minimised)
			{
				for (Layer* layer : ls.GetLayers())
				{
					layer->OnUpdate(m_DeltaT);
				}
			}
			 
			m_Window->OnUpdate();
		}
		 
	}

	bool Application::OnWindowClose(WindowCloseEvent& wc)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& wre)
	{
		if(wre.GetWidth() == 0 || wre.GetHeight() == 0)
		{
			m_Minimised = true;
		}

		m_Minimised = false;
		RenderCommand::WindowResize(0, 0, wre.GetWidth(), wre.GetHeight());
		return false;
	}
}