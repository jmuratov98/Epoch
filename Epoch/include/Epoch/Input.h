#pragma once

#include "Epoch/Core.h"

namespace Epoch {

	class EGE_API Input
	{
	protected:
		Input() = default;
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		inline static bool isKeyPressed(int keycode) { return cm_Singleton->isKeyPressedImpl(keycode); }

		inline static bool isMouseButtonPressed(int button) { return cm_Singleton->isMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> getMousePos() { return cm_Singleton->getMousePosImpl(); }
		inline static float getX() { return cm_Singleton->getXImpl(); }
		inline static float getY() { return cm_Singleton->getYImpl(); }

	protected:
		virtual bool isKeyPressedImpl(int keycode) = 0;
		
		virtual bool isMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> getMousePosImpl() = 0;
		virtual float getXImpl() = 0;
		virtual float getYImpl() = 0;

	private:
		static Input* cm_Singleton;
	};

}