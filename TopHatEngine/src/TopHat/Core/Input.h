#pragma once

namespace TopHat
{
	class Input
	{
	public:
		inline static bool IsKeyDown(int keycode) { return s_Instance->IsKDown(keycode); }

		inline static bool IsMouseButtonDown(int button) { return s_Instance->IsMBDown(button); }

		inline static  std::pair<float, float> GetMousePos() { return s_Instance->MP(); }

		inline static float GetMouseX() { return s_Instance->MPX(); }

		inline static float GetMouseY() { return s_Instance->MPY(); }
	protected:
		virtual bool IsKDown(int keycode) = 0;
		virtual bool IsMBDown(int keycode) = 0;
		virtual std::pair<float, float> MP() = 0;
		virtual float MPX() = 0;
		virtual float MPY() = 0;
	private:
		static Input* s_Instance;
	};

}