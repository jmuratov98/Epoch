#pragma once

#include "Epoch/Core.h"

namespace Epoch {
	
	enum class ShaderDataType { None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4, Boolean };

	// --------------------------------------------------------------------------------------------
	// ----------------- Buffer Layout ------------------------------------------------------------
	// --------------------------------------------------------------------------------------------

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement() { }
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false);

		uint32_t getComponentCount() const;
	};

	class BufferLayout
	{
	public:
		BufferLayout() { }
		BufferLayout(const std::initializer_list<BufferElement>& element);

		// Getters
		inline uint32_t getStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& getElements() const { return m_Elements; }

		// Iterators
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void calculateOffsetAndStride();

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	// --------------------------------------------------------------------------------------------
	// ----------------- Vertex Buffer ------------------------------------------------------------
	// --------------------------------------------------------------------------------------------

	class EGE_API VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const BufferLayout& getBufferLayout() = 0;
		virtual void setBufferLayout(const BufferLayout& layout) = 0;

		static Ref<VertexBuffer> create(float* vertices, uint32_t size);
	};

	// --------------------------------------------------------------------------------------------
	// ----------------- Index Buffer -------------------------------------------------------------
	// --------------------------------------------------------------------------------------------

	class EGE_API IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual uint32_t getCount() const = 0;

		static Ref<IndexBuffer> create(uint32_t* indices, uint32_t count);
	};

}