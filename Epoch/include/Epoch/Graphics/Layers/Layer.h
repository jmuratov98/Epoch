#pragma once

#include "Epoch/Core.h"
#include "Epoch/Events/Event.h"

namespace Epoch {

	class EGE_API Layer
	{
	public: // Public Functions
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void onAttach() { }
		virtual void onDetach() { }
		virtual void onUpdate() { }
		virtual void onEvent(Event& e) { }

		inline const std::string& getName() const { return m_Name; }

	protected:
		std::string m_Name;
	};

}