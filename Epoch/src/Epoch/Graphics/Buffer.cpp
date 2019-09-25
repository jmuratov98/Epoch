#include "pch.h"
#include "Epoch/Graphics/Buffer.h"

#include "Epoch/Graphics/Renderer.h"

#include "Epoch/Platform/OpenGL/OpenGLBuffer.h"

namespace Epoch {

	static uint32_t shader_data_type_size(ShaderDataType type)
	{
		switch (type)
		{
		case Epoch::ShaderDataType::Float:		return 4;
		case Epoch::ShaderDataType::Float2:		return 4 * 2;
		case Epoch::ShaderDataType::Float3:		return 4 * 3;
		case Epoch::ShaderDataType::Float4:		return 4 * 4;
		case Epoch::ShaderDataType::Int:		return 4;
		case Epoch::ShaderDataType::Int2:		return 4 * 2;
		case Epoch::ShaderDataType::Int3:		return 4 * 3;
		case Epoch::ShaderDataType::Int4:		return 4 * 4;
		case Epoch::ShaderDataType::Mat3:		return 4 * 3 * 3;
		case Epoch::ShaderDataType::Mat4:		return 4 * 4 * 4;
		case Epoch::ShaderDataType::Boolean:	return 1;
		default:								EGE_CORE_ASSERT(false, "Unknown Shader Data Type!"); return 0;
		}
	}

	// --------------------------------------------------------------------------------------------
	// ----------------- Buffer Layout ------------------------------------------------------------
	// --------------------------------------------------------------------------------------------

	BufferElement::BufferElement(ShaderDataType type, const std::string& name, bool normalized)
		: Name(name), Type(type), Size(shader_data_type_size(type)), Offset(0), Normalized(normalized)
	{
	}

	uint32_t BufferElement::getComponentCount() const
	{
		switch (Type)
		{
		case Epoch::ShaderDataType::Float:		return 1;
		case Epoch::ShaderDataType::Float2:		return 2;
		case Epoch::ShaderDataType::Float3:		return 3;
		case Epoch::ShaderDataType::Float4:		return 4;
		case Epoch::ShaderDataType::Int:		return 1;
		case Epoch::ShaderDataType::Int2:		return 2;
		case Epoch::ShaderDataType::Int3:		return 3;
		case Epoch::ShaderDataType::Int4:		return 4;
		case Epoch::ShaderDataType::Mat3:		return 3 * 3;
		case Epoch::ShaderDataType::Mat4:		return 4 * 4;
		case Epoch::ShaderDataType::Boolean:	return 1;
		default:								EGE_CORE_ASSERT(false, "Unknown Shader Data Type!"); return 0;
		}
	}

	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& element)
		: m_Elements(element)
	{
		calculateOffsetAndStride();
	}

	void BufferLayout::calculateOffsetAndStride()
	{
		uint32_t offset = 0;
		m_Stride = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}

	// --------------------------------------------------------------------------------------------
	// ----------------- Vertex Buffer ------------------------------------------------------------
	// --------------------------------------------------------------------------------------------

	Ref<VertexBuffer> VertexBuffer::create(float* vertices, uint32_t size)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:			EGE_CORE_ASSERT(false, "None is not yet implemented"); return nullptr;
		case RendererAPI::API::OpenGL:			return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		default:								EGE_CORE_ASSERT(false, "Unknown render API"); return nullptr;
		}
	}

	// --------------------------------------------------------------------------------------------
	// ----------------- Index Buffer -------------------------------------------------------------
	// --------------------------------------------------------------------------------------------

	Ref<IndexBuffer> IndexBuffer::create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:			EGE_CORE_ASSERT(false, "None is not yet implemented"); return nullptr;
		case RendererAPI::API::OpenGL:			return std::make_shared<OpenGLIndexBuffer>(indices, count);
		default:								EGE_CORE_ASSERT(false, "Unknown render API"); return nullptr;
		}
	}

}