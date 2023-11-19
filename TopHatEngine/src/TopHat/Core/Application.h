#pragma once
 

#include "Window.h"
#include "LayerStack.h"
#include "TopHat/Events/Events.h"
#include "TopHat/Events/ApplicationEvents.h"
#include "DeltaTime.h"
 

namespace TopHat
{
	class  Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();	
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& wc);
		bool OnWindowResize(WindowResizeEvent& wre);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true, m_Minimised = false;
		LayerStack ls;
		static Application* s_Instance;
		DeltaTime m_DeltaT = DeltaTime();
	 
	};

	Application* CreateGame();
}

