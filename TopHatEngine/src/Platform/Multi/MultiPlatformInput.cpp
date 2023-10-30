#include "THPrecomp.h"
#include "MultiPlatformInput.h"
#include "GLFW/glfw3.h"
#include "TopHat/Application.h"

namespace TopHat
{
#ifdef TH_PLATFORM_MULTI
	Input* Input::s_Instance = new MultiPlatformInput();
#endif

	bool MultiPlatformInput::IsKDown(int keycode)
	{

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool MultiPlatformInput::IsMBDown(int button)
	{

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> MultiPlatformInput::MP()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xP, yP;
		glfwGetCursorPos(window, &xP, &yP);
		return { (float)xP, (float)yP };
	}

	float MultiPlatformInput::MPX()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto [x, y] = MP();
		return x;
	}
	float MultiPlatformInput::MPY()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto [x, y] = MP();
		return y;
	}
}
