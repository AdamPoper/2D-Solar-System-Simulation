#include "Texture.h"
#include <iostream>
Texture::Texture() {}

Texture::Texture(const char* filePath)
	: m_renderID(0), m_width(0), m_height(0), m_bpp(0), m_dataBuffer(nullptr)
{
	glGenTextures(1, &m_renderID);
	glBindTexture(GL_TEXTURE_2D, m_renderID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	stbi_set_flip_vertically_on_load(1);
	m_dataBuffer = stbi_load(filePath, &m_width, &m_height, &m_bpp, 4);
	if (!m_dataBuffer)
		std::cout << "Failed to load texture!" << std::endl;
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_dataBuffer);
		stbi_image_free(m_dataBuffer);
	}

}
void Texture::bind(unsigned int slot) const
{
	glBindTexture(GL_TEXTURE_2D, m_renderID + slot);
}
void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}