#pragma once

#include "Epoch/Core.h"
#include "Epoch/Graphics/Buffer.h"

namespace Epoch {

	class EGE_API VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) = 0;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const = 0;

		static VertexArray* create();
	};

}