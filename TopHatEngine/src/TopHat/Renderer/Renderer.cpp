#include "THPrecomp.h"
#include "Renderer.h"
#include "Platform/RenderAPI/OpenGL/OpenGLRenderer.h"
#include "Platform/RenderAPI/OpenGL/OpenGLShader.h"
namespace TopHat
{
	RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;
	RenderAPI* RenderCommand::s_RenderAPi = new OpenGLRenderAPI();
	Renderer::SceneData* Renderer::m_SD = new Renderer::SceneData();

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene(Camera& cam)
	{
		m_SD->m_ProjectionViewMatrix = cam.GetProjectionViewMatrix();
	}
 
	void Renderer::Submit(std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray, glm::mat4 trans)
	{
		 
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("a_ViewProj", m_SD->m_ProjectionViewMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("a_Trans", trans);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::EndScene()
	{
		
	}



}
