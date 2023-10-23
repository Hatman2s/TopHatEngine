#include "THPrecomp.h"
#include "OpenGLContext.h"

namespace TopHat
{
	OpenGLContext::OpenGLContext(GLFWwindow* win): m_Window(win)
	{
		TH_FRAMEWORK_ASSERTS(m_Window, "Window passed does not exist");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TH_FRAMEWORK_ASSERTS(status, "Failed to Load Glad!")
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}

}