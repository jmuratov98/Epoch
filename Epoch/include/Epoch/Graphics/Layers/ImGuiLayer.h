#pragma once

#include "Epoch/Graphics/Layers/Layer.h"

namespace Epoch {

	class EGE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onImGuiRender() override;

		void begin();
		void end();

	private:
		float m_Time = 0.0f;
	};

}