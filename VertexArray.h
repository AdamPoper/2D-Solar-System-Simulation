#pragma once
#include "VertexBufferlayout.h"
#include "VertexBuffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void bind() const;
	void unbind() const;
	void addBuffer(const VertexBuffer&, const VertexBufferLayout&);

private:
	unsigned int m_renderID;
};