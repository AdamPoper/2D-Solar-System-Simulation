#include "VertexArray.h"

VertexArray::VertexArray() : m_renderID(0)
{
	glGenVertexArrays(1, &m_renderID);
	glBindVertexArray(m_renderID);
}
VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_renderID);
}
void VertexArray::bind() const
{
	glBindVertexArray(m_renderID);
}
void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	this->bind();
	vb.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized, layout.getStride(), (void*)offset);
		offset += (elements[i].count * LayoutElements::getSizeofType(elements[i].type));
	}
}