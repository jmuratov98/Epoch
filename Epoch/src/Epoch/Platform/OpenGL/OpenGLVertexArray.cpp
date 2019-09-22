#include "pch.h"
#include "Epoch/Platform/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Epoch {

	static unsigned int shader_data_type_to_opengl_base_type(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:			return GL_FLOAT;
		case ShaderDataType::Float2:		return GL_FLOAT;
		case ShaderDataType::Float3:		return GL_FLOAT;
		case ShaderDataType::Float4:		return GL_FLOAT;
		case ShaderDataType::Mat3:			return GL_FLOAT;
		case ShaderDataType::Mat4:			return GL_FLOAT;
		case ShaderDataType::Int:			return GL_INT;
		case ShaderDataType::Int2:			return GL_INT;
		case ShaderDataType::Int3:			return GL_INT;
		case ShaderDataType::Int4:			return GL_INT;
		case ShaderDataType::Boolean:		return GL_BOOL;
		default:							EGE_CORE_ASSERT(false, "Unknown Shader Data Type!"); return 0;
		}
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer)
	{
		EGE_CORE_ASSERT(buffer->getBufferLayout().getElements().size(), "The Vertex Buffer has no elements");

		glBindVertexArray(m_RendererID);
		buffer->bind();

		const auto& layout = buffer->getBufferLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(m_VertexBufferIndex,
				element.getComponentCount(),
				shader_data_type_to_opengl_base_type(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.getStride(),
				(const void*)element.Offset);
			m_VertexBufferIndex++;
		}

		m_VertexBuffers.push_back(buffer);
	}

	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer)
	{
		glBindVertexArray(m_RendererID);
		buffer->bind();

		m_IndexBuffer = buffer;
	}

}