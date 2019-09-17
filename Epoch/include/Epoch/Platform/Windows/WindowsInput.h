#pragma once

#include "Epoch/Input.h"

namespace Epoch {

	class WindowsInput : public Input
	{
	protected:
		virtual bool isKeyPressedImpl(int keycode) override;

		virtual bool isMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> getMousePosImpl() override;
		virtual float getXImpl() override;
		virtual float getYImpl() override;
};

}