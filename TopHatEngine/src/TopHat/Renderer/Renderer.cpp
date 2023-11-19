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
 
	void Renderer::Submit(Ref<Shader> shader, const Ref<VertexArray>& vertexArray, glm::mat4 trans)
	{
		if(shader == nullptr)
		{
			TH_FRAMEWORK_ASSERTS(false, "Shader does not exist. Is the Shader Name Correct?")
		}
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("a_ViewProj",m_SD->m_ProjectionViewMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("a_Trans", trans);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::EndScene()
	{
		
	}



}
