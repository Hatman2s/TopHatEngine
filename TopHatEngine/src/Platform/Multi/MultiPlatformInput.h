#pragma once

#include "TopHat/Core/Input.h"

namespace TopHat
{
	class MultiPlatformInput: public Input
	{
	protected:
		bool IsKDown(int keycode) override;
		bool IsMBDown(int keycode) override;
		std::pair<float, float> MP() override;
		float MPX() override;
		float MPY() override;
	};
}
