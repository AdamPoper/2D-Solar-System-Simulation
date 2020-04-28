#include "Planet.h"

Planet::Planet(const char* filePath, float rad, float s, const float* data, size_t sizeBytes)
	: m_actualRadius(rad), m_speed(s), m_degrees(0.0f), m_vertexBuffer(data, sizeBytes), m_scaleFactor(1.0f)
{
	m_texture = new Texture(filePath);
	m_scaleRadius = m_actualRadius;
	m_child = nullptr;
}
Planet::Planet(const char* filepath, const float* data, size_t size)
	: m_vertexBuffer(data, size), m_actualRadius(0), m_degrees(0), m_speed(0)
{
	m_texture = new Texture(filepath);
	m_child = nullptr;
}
Planet::Planet() : m_actualRadius(0), m_degrees(0), m_speed(0), m_vertexBuffer(nullptr, 0), m_child(nullptr) {}

Planet::~Planet()
{
	delete m_texture;
}
void Planet::bind() const
{
	m_texture->bind();
	m_vertexBuffer.bind();
}
void Planet::calcPosition() 
{
	float trans_x, trans_y;
	trans_x = cos(glm::radians(m_degrees)) * m_scaleRadius;
	trans_y = sin(glm::radians(m_degrees)) * m_scaleRadius;
	m_degrees >= 360.0f ? m_degrees = 0.0f : m_degrees += m_speed;
	m_rotation >= 360.0f ? m_rotation = 0.0f : m_rotation += (m_speed / 2.0f);
	glm::mat4 trans(1.0f);
	m_translation = glm::vec3(trans_x, trans_y, 0.0f);
	m_model = glm::translate(trans, m_translation);
	m_model = glm::rotate(m_model, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	m_model = glm::scale(m_model, glm::vec3(m_scaleFactor));
}
const glm::mat4& Planet::getModel() const
{
	return m_model;
}
const glm::vec3& Planet::getTranslation()
{
	return m_translation;
}
const VertexBuffer& Planet::retrieveVertexBuffer()
{
	return m_vertexBuffer;
}
void Planet::scaleUp(double s)
{
	m_scaleFactor += s;
	m_scaleRadius = m_actualRadius * m_scaleFactor;
}
void Planet::scaleDown(double s)
{
	m_scaleFactor -= s;
	m_scaleRadius = m_actualRadius * m_scaleFactor;
}
void Planet::setMoon(Moon* m_ptr)
{
	m_child = m_ptr;
}
bool Planet::hasMoon()
{
	return (m_child != nullptr);
}

Moon::Moon(const char* filePath, float rad, float s, const float* data, size_t sizeBytes)
	: m_actualRadius(rad), m_speed(s), m_degrees(0.0f), m_vertexBuffer(data, sizeBytes), m_scaleFactor(1.0f)
{
	m_texture = new Texture(filePath);
	m_scaleRadius = m_actualRadius;
}
Moon::Moon(const char* filePath, float rad, float s, const float* data, size_t sizeBytes, const Planet* p_ptr)
	: m_actualRadius(rad), m_speed(s), m_degrees(0.0f), m_vertexBuffer(data, sizeBytes), m_scaleFactor(1.0f)
{
	m_texture = new Texture(filePath);
	m_scaleRadius = m_actualRadius;
	m_parent = p_ptr;
}
void Moon::calcPosition() 
{
	this->m_model = m_parent->getModel();
}
Moon::~Moon()
{
	delete m_texture;
}

