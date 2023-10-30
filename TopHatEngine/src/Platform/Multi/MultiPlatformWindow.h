#pragma once

#include "TopHat/Window.h"
#include "GLFW/glfw3.h"
#include "TopHat/Renderer/Renderer.h"

namespace TopHat
{
	class  MultiPlatformWindow : public Window
	{
	public:
		MultiPlatformWindow(const WindowProperties& winprops);
		virtual ~MultiPlatformWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.width; }
		inline unsigned int GetHeight() const override { return m_Data.height; }

		inline virtual void* GetNativeWindow() const { return m_Window; }

		inline void SetVsync(bool enabled) override;
		inline bool IsVsync() const override { return m_Data.isVsync; }
		 

		inline void OnEventCallback(const EventCallbackFn& eventCall) override { m_Data.eventCallback = eventCall; }
	protected:
		virtual void Init(const WindowProperties& wp);
		virtual void Shutdown();
	private:

		GLFWwindow* m_Window;
		RenderContext* m_Context;
		struct WinData
		{
			std::string title;
			unsigned int width;
			unsigned int height;
			bool isVsync;
			EventCallbackFn eventCallback;
		};

		WinData m_Data;

	};
}