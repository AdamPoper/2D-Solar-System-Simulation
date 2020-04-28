#pragma once
#include "GL/glew.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class ShaderProgram
{
public:
	ShaderProgram(const char*, const char*);
	ShaderProgram();
	~ShaderProgram();
	void bind() const;
	void unbind() const;
	void compileShader(std::string&, unsigned int);
	void loadShader(const char*, std::string&);
	void deleteProgram() const;
	unsigned int getRenderID() const;
	void setUniform4f(const char*, float, float, float, float);
	void setUniform1i(const char*, int);
	void setUniformMat4(const char*, glm::mat4&);
private:
	unsigned int m_renderID;
	unsigned int vsID;
	unsigned int fsID;
	std::string fs_src, vs_src;

};