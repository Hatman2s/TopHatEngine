#pragma once

#include "TopHat/Renderer/RenderContext.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace TopHat
{
	class OpenGLContext : public RenderContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_Window;
	};
}