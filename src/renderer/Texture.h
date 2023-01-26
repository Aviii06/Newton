#pragma once

#include "Renderer.h"
#include "stb_image/stb_image.h"

namespace Vivid
{
	class Texture
	{
	private:
		unsigned int m_RendererID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		int m_Width, m_Height, m_BPP;

	public:
		Texture();

		Texture(const std::string& path);

		~Texture();

		void Bind(unsigned int slot = 0) const;

		void Unbind() const;

		inline unsigned int getRendererID() const { return m_RendererID; }

		inline int GetWidth() const { return m_Width; }

		inline int GetHeight() const { return m_Height; }
	};
}