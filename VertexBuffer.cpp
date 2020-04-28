#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() : m_renderID(0) {}

VertexBuffer::VertexBuffer(const void* data, size_t size)
	: m_size(size)
{
	glGenBuffers(1, &m_renderID);
	glBindBuffer(GL_ARRAY_BUFFER, m_renderID);
	glBufferData(GL_ARRAY_BUFFER, m_size, data, GL_STATIC_DRAW);
}
void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_renderID);
}
void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
size_t VertexBuffer::getSize() const
{
	return m_size;
}
unsigned int VertexBuffer::getID() const
{
	return m_renderID;
}