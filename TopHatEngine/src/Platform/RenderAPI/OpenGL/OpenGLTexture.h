#pragma once

#include "TopHat/Renderer/Texture.h"

namespace TopHat
{
	class OpenGLTexture : public Texture2D
	{
	public:
		OpenGLTexture(const std::string& path);
		virtual ~OpenGLTexture();
		uint32_t GetWidth() const override { return m_Width; }
		uint32_t GetHeight() const override { return m_Height; }
		void Bind(uint32_t slot = 0) const override;
	private:
		uint32_t m_Width, m_Height;
		uint32_t m_RenderID;
		std::string m_Path;
	};
}
