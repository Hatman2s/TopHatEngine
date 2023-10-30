#include "THPrecomp.h"
#include "WindowsInput.h"
#include "GLFW/glfw3.h"
#include "TopHat/Application.h"

namespace TopHat
{
#ifdef TH_PLATFORM_WINDOWS
	Input* Input::s_Instance = new WindowsInput();
#endif

	bool WindowsInput::IsKDown(int keycode)
	{
		
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMBDown(int button)
	{

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::MP()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xP, yP;
		glfwGetCursorPos(window, &xP, &yP);
		return { (float)xP, (float)yP };
	}

	float WindowsInput::MPX()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto [x, y] = MP();
		return x;
	}
	float WindowsInput::MPY()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto [x, y] = MP();
		return y;
	}
}