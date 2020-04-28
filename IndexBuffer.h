#pragma once
#include <GL/glew.h>
class IndexBuffer
{
public:
	IndexBuffer(const void*, size_t, unsigned int);
	IndexBuffer();

	size_t getSize() const;
	unsigned int getID() const;
	unsigned int getIndicies() const;
	void bind() const;
	void unbind() const;

private:
	unsigned int m_renderID;
	size_t m_size; // size in bytes
	unsigned int m_indicies;  // number of indices to be rendered
};