#include "pch.h"
#include "Epoch/Graphics/Layers/LayerStack.h"

namespace Epoch {

	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			layer->onDetach();
			delete layer;
		}
	}

	void LayerStack::pushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerIndex, layer);
		m_LayerIndex++;
		layer->onAttach();
	}

	void LayerStack::popLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerIndex, layer);
		if (it != m_Layers.begin() + m_LayerIndex)
		{
			layer->onDetach();
			m_Layers.erase(it);
			m_LayerIndex--;
		}
	}

	void LayerStack::pushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
		overlay->onAttach();
	}

	void LayerStack::popOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin() + m_LayerIndex, m_Layers.end(), overlay);
		if (it != m_Layers.begin() + m_LayerIndex)
		{
			overlay->onDetach();
			m_Layers.erase(it);
		}
	}

}