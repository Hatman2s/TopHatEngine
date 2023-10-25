#pragma once
#include "Handler.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Events.h"
#include "Events/ApplicationEvents.h"

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"

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
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack ls;
		static Application* s_Instance;

		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<Shader> shader;
		std::shared_ptr<VertexArray> vertexArray;
		std::shared_ptr<IndexBuffer> indexBuffer;
	};

	Application* CreateGame();
}

