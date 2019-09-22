#pragma once

#include "Epoch/Graphics/RendererAPI.h"

namespace Epoch {

	class RendererCommand
	{
	public:
		inline static void init() { cm_RendererAPI->init(); }

		inline static void setClearColor(const glm::vec4& color) { cm_RendererAPI->setClearColor(color); }
		inline static void clear() { cm_RendererAPI->clear(); }

		inline static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) { cm_RendererAPI->drawIndexed(vertexArray); }

	private:
		static RendererAPI* cm_RendererAPI;
	};

}