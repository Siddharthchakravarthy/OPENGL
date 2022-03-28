#pragma once

#include "Renderer.h"
class Texture
{
public:
	unsigned int m_RendererID_for_texre;
	std::string m_Filepath;
	int m_Width, m_Height, m_BPP; // m_BPP andre bytes per pixels anta
	unsigned char* m_LocalBuffer;
public:
	Texture(const std::string &path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void UnBind();

	inline int GetTextureWidth() const {// const munde yaakandre it'll return a constant variable anta
		return m_Width;
	}
	inline int GetTextureHeight() const { // idu ashte change madak aagbaardu this variable na if we're trying to access this one
		return m_Height;
	}
};

