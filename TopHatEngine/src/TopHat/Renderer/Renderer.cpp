#include "THPrecomp.h"
#include "Renderer.h"
#include "Platform/RenderAPI/OpenGL/OpenGLRenderer.h"
namespace TopHat
{
	RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;
	RenderAPI* RenderCommand::s_RenderAPi = new OpenGLRenderAPI();


	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene()
	{
		
	}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}


}
