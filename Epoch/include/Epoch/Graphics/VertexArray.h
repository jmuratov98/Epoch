#pragma once

#include "Epoch/Core/Core.h"
#include "Epoch/Graphics/Buffer.h"

namespace Epoch {

	class EGE_API VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		
		virtual void addVertexBuffer(const Ref<VertexBuffer>& buffer) = 0;
		virtual void setIndexBuffer(const Ref<IndexBuffer>& buffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& getIndexBuffer() const = 0;

		static Ref<VertexArray> create();
	};

}