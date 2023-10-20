#include "THPrecomp.h"
#include "WindowsWindow.h"

namespace TopHat
{
	static bool GLFWInit = false;
	Window* Window::Create(const WindowProperties& wp)
	{
		return new WindowsWindow(wp);
	}
	WindowsWindow::WindowsWindow(const WindowProperties& winprops)
	{
		Init(winprops);
	}
	WindowsWindow::~WindowsWindow() 
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProperties& wp)
	{
		m_Data.title = wp.Title;
		m_Data.width = wp.Width;
		m_Data.height = wp.Height;

		if(!GLFWInit)
		{
			bool status = glfwInit();
			TH_FRAMEWORK_ASSERTS(status, "Could Not Initialise GLFW");
			GLFWInit = true;
		}
		m_Window = glfwCreateWindow(m_Data.width, m_Data.height, m_Data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVsync(true);
	
	}
	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVsync(bool enabled)
	{
		if(enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
		m_Data.isVsync = enabled;

	}

}