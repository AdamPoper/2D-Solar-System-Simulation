#include "IndexBuffer.h"

IndexBuffer::IndexBuffer() : m_renderID(0), m_size(0) {}

IndexBuffer::IndexBuffer(const void* data, size_t size, unsigned int num)
	: m_size(size), m_indicies(num)
{
	glGenBuffers(1, &m_renderID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size, data, GL_STATIC_DRAW);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderID);
}
void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
size_t IndexBuffer::getSize() const
{
	return m_size;
}
unsigned int IndexBuffer::getID() const
{
	return m_renderID;
}
unsigned int IndexBuffer::getIndicies() const
{
	return m_indicies;
}