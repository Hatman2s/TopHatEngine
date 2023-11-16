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
		 void WindowResize(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		 void Clear() override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};

 
}
