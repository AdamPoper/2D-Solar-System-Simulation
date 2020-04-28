#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
	: m_renderID(0), vsID(0), fsID(0) {}

ShaderProgram::ShaderProgram(const char* vs_path, const char* fs_path)
	: m_renderID(0), fsID(0), vsID(0), vs_src(), fs_src()
{
	vsID = glCreateShader(GL_VERTEX_SHADER);
	fsID = glCreateShader(GL_FRAGMENT_SHADER);
	loadShader(vs_path, vs_src);
	loadShader(fs_path, fs_src);
	compileShader(vs_src, vsID);
	compileShader(fs_src, fsID);
	m_renderID = glCreateProgram();
	glAttachShader(m_renderID, vsID);
	glAttachShader(m_renderID, fsID);
	glLinkProgram(m_renderID);
	glValidateProgram(m_renderID);
	glUseProgram(m_renderID);

	glDeleteShader(fsID);
	glDeleteShader(vsID);
}
ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_renderID);
}
void ShaderProgram::loadShader(const char* path, std::string& src)
{
	std::ifstream stream(path);

	if (stream.fail())
		std::cout << "failed to open file" << std::endl;
	std::string line;
	std::stringstream ss;

	while (getline(stream, line))
		ss << line << '\n';

	src = ss.str();
}
void ShaderProgram::compileShader(std::string& source, unsigned int id)
{
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
}
void ShaderProgram::deleteProgram() const
{
	glDeleteProgram(m_renderID);
}
void ShaderProgram::bind() const
{
	glUseProgram(m_renderID);
}
void ShaderProgram::unbind() const
{
	glUseProgram(0);
}
unsigned int ShaderProgram::getRenderID() const
{
	return m_renderID;
}
void ShaderProgram::setUniform4f(const char* name, float v1, float v2, float v3, float v4)
{
	int location = glGetUniformLocation(m_renderID, name);
	glUniform4f(location, v1, v2, v3, v4);
}
void ShaderProgram::setUniform1i(const char* name, int value)
{
	int location = glGetUniformLocation(m_renderID, name);
	glUniform1i(location, value);
}
void ShaderProgram::setUniformMat4(const char* name, glm::mat4& mat)
{
	int location = glGetUniformLocation(m_renderID, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}
