#pragma once
#include <GL/glew.h>
#include <vector>
struct LayoutElements
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int getSizeofType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:         return 4;
			case GL_UNSIGNED_INT:  return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}
	}
};
class VertexBufferLayout
{
public:
	VertexBufferLayout() : m_stride(0) {}
	
	template<typename type>
	void push(unsigned int count)
	{
		if (std::is_same_v<type, float>)
			m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		else if (std::is_same_v<type, unsigned int>)
			m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		else if (std::is_same_v<type, unsigned char>)
			m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
		m_stride += sizeof(type) * count;
	}

	inline const std::vector<LayoutElements>& getElements() const { return m_elements; }
	const unsigned int getStride() const { return m_stride; }

private:
	std::vector<LayoutElements> m_elements;
	unsigned int m_stride;
};