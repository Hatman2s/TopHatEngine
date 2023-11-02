#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "TopHat/Renderer/Renderer.h"
namespace TopHat
{
	class Renderer;
	class OpenGLContext : public RenderContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_Window;
	};

	class OpenGLRenderAPI : public RenderAPI
	{
	public:
		 void Init() override;
		 void SetClearColor(const glm::vec4& color) override;
		 void Clear() override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};

 
}
