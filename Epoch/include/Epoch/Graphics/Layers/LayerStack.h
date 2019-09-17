#pragma once

#include "Epoch/Core.h"
#include "Epoch/Graphics/Layers/Layer.h"

namespace Epoch {

	class EGE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void pushLayer(Layer* layer);
		void popLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerIndex = 0;
	};
	
}