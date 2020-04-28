#pragma once
#include "GL/glew.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

class Renderer
{
public:
	Renderer();
	void draw(const VertexArray&, const IndexBuffer&, const ShaderProgram&);
};