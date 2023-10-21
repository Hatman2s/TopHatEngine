#include "THPrecomp.h"
#include "WindowsWindow.h"
#include "TopHat/Events/ApplicationEvents.h"
#include "TopHat/Events/KeyEvents.h"
#include "TopHat/Events/MouseEvents.h"

namespace TopHat
{
	static bool GLFWInit = false;

	static void GLFWErrorCallback( int error, const char* descript)
	{
		TH_ENGINE_ERROR("GLFW ERROR ({0}): {1}", error, descript);
	}
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
			glfwSetErrorCallback(GLFWErrorCallback);
			GLFWInit = true;
		}
		m_Window = glfwCreateWindow(m_Data.width, m_Data.height, m_Data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVsync(true);

		//glfw event callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WinData& data = *(WinData*)glfwGetWindowUserPointer(window);

				data.width = width;
				data.height = height;

				WindowResizeEvent e(width, height);
				data.eventCallback(e);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WinData& data = *(WinData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent e;
				data.eventCallback(e);

			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WinData& data = *(WinData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyDownEvent e(key, 0);
						data.eventCallback(e);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyDownEvent e(key, 1);
						data.eventCallback(e);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyUpEvent e(key);
						data.eventCallback(e);
						break;
					}
				default:
					break;
				}
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WinData& data = *(WinData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonDownEvent e(button);
					data.eventCallback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonUpEvent e(button);
					data.eventCallback(e);
					break;
				}
				default:
					break;
				}

			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoff, double yoff) 
			{
				WinData& data = *(WinData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent e((float)xoff, (float)yoff);
				data.eventCallback(e);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WinData& data = *(WinData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent e((float)xpos, (float)ypos);
				data.eventCallback(e);
			});
	
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