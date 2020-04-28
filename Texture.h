#pragma once
#include "stb_image/stb_image.h"
#include "GL/glew.h"
class Texture
{
public:
	Texture();
	Texture(const char*);
	void bind(unsigned int slot = 0) const;
	void unbind() const;
private:
	unsigned char* m_dataBuffer;
	unsigned int m_renderID;	
	int m_width, m_height, m_bpp;
};