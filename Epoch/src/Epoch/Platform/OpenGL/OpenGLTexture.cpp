#include "pch.h"
#include "Epoch/Platform/OpenGL/OpenGLTexture.h"

#include <glad/glad.h>

#include <stb/stb_image.h>

namespace Epoch {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath)
		: m_FilePath(filepath)
	{
		int width, height, channels;

		stbi_set_flip_vertically_on_load(1);
		unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
		EGE_CORE_ASSERT(data, "Failed to load image");
		m_Width = width;
		m_Height = height;
			
		unsigned int internal_format = 0, data_format = 0;
		if (channels == 4)
		{
			internal_format = GL_RGBA8;
			data_format = GL_RGBA;
		}
		else if (channels == 3)
		{
			internal_format = GL_RGB8;
			data_format = GL_RGB;
		}
		

		EGE_CORE_ASSERT(internal_format & data_format, "Unsopported format");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internal_format, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, data_format, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

}