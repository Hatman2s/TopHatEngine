#include "THPrecomp.h"
#include "Application.h"
#include "Events/ApplicationEvents.h"
#include "Log.h"
#include "glm.hpp"
#include "glad/glad.h"

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
		m_Window->OnEventCallback(EVENT_BIND(OnEvent));
		Renderer::Init();
		float vertices[3*7]
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,1.0f
		};
		vertexArray.reset(VertexArray::Create());
		vertexArray->Bind();
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout =
		{
			{ TopHat::ShaderVarType::Float3, "a_Pos" },
			{TopHat::ShaderVarType::Float4, "a_Color"}
		};
		vertexBuffer->SetBufferLayout(layout);
		vertexArray->AddVertexBuf(vertexBuffer);
		uint32_t indices[3] = { 0, 1, 2 };
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		vertexArray->AddIndexBuf(indexBuffer);
		shader.reset(Shader::Create("C:\\Dev\\GameDev\\TopHatEngine\\Game\\Shader.txt.txt"));

		
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
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();
			shader->Bind();
			Renderer::Submit(vertexArray);

			/*for (Layer* layer : ls.GetLayers())
			{
				layer->OnUpdate();
			}*/
				
			m_Window->OnUpdate();
		}
		 
	}

	bool Application::OnWindowClose(WindowCloseEvent& wc)
	{
		m_Running = false;
		return true;
	}
}