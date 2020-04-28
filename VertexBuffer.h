#pragma once
#include <GL/glew.h>
class VertexBuffer
{
public:
	VertexBuffer();
	VertexBuffer(const void*, size_t);

	void bind() const;
	void unbind() const;

	unsigned int getID() const;
	size_t getSize() const;

private:
	unsigned int m_renderID;
	size_t m_size;  // size in bytes
};