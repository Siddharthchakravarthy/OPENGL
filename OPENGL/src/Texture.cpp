#include "Texture.h"

#include "Vendor/stb/stb_image.h"


Texture::Texture(const std::string& path) :
	m_RendererID_for_texre(0), m_Filepath(path), m_Width(0), m_Height(0), m_BPP(0), m_LocalBuffer(nullptr)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
	glGenTextures(1, &m_RendererID_for_texre);
	glBindTexture(GL_TEXTURE_2D, m_RendererID_for_texre);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);


	if (m_LocalBuffer) {
		stbi_image_free(m_LocalBuffer);
	}

}
Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID_for_texre));
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot); // idu slot specify maadoodu out of 32 texture slots
	glBindTexture(GL_TEXTURE_2D, m_RendererID_for_texre);
}

void Texture::UnBind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
