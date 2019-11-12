#pragma once

#include "Epoch/Graphics/RendererAPI.h"

namespace Epoch {

	class RendererCommand
	{
	public:
		inline static void init() { cm_RendererAPI->init(); }
		inline static void setViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { cm_RendererAPI->setViewPort(x, y, width, height); }

		inline static void setClearColor(const glm::vec4& color) { cm_RendererAPI->setClearColor(color); }
		inline static void clear() { cm_RendererAPI->clear(); }

		inline static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) { cm_RendererAPI->drawIndexed(vertexArray); }

	private:
		static Scope<RendererAPI> cm_RendererAPI;
	};

}