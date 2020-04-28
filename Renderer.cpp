#include "Renderer.h"

Renderer::Renderer() {}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shader)
{
	va.bind();
	ib.bind();
	shader.bind();
	glDrawElements(GL_TRIANGLES, ib.getIndicies(), GL_UNSIGNED_INT, nullptr);
}