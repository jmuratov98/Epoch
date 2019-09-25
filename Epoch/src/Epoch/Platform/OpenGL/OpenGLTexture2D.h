#pragma once

#include "Epoch/Graphics/Texture.h"

namespace Epoch {

	class OpenGLTexture2D : public Texture2D
	{
		OpenGLTexture2D(const std::string& filepath);
		virtual ~OpenGLTexture2D();

		virtual uint32_t getWidth() const override;
		virtual uint32_t getHeight() const override;
		
		virtual void bind() const override;

	};

}