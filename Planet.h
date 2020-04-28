#pragma once
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "VertexBuffer.h"
#include "vector2f.h"

// prototype for moon sub class
class Moon;

class Planet
{
public:
	Planet(const char*, float, float, const float*, size_t);
	Planet(const char*, const float*, size_t);
	Planet();
	~Planet();
	const glm::mat4& getModel() const;
	const glm::vec3& getTranslation();
	virtual void calcPosition();
	void bind() const;
	//void setVertexBuffer();
	const VertexBuffer& retrieveVertexBuffer();
	void scaleUp(double);
	void scaleDown(double);
	bool hasMoon();
	void setMoon(Moon*);
private:

	Texture* m_texture;
	glm::vec3 m_translation;
	glm::mat4 m_model;
	float m_actualRadius, m_scaleRadius, m_speed, m_degrees, m_rotation, m_scaleFactor;
	VertexBuffer m_vertexBuffer;
	vector2f m_size;
	size_t m_sizeBytes; // size in bytes of the data for the vertex buffer
	float m_data[16];
	Moon* m_child;
};

class Moon : public Planet
{
public:
	Moon();
	Moon(const char*, float, float, const float*, size_t, const Planet*);
	Moon(const char*, float, float, const float*, size_t);
	~Moon();
	void setParent(const Planet*);
	void calcPosition() override;
private:
	glm::mat4 m_model;
	Texture* m_texture;
	glm::vec3 m_translation;
	float m_actualRadius, m_scaleRadius, m_speed, m_degrees, m_rotation, m_scaleFactor;
	VertexBuffer m_vertexBuffer;
	size_t m_sizeBytes;
	float m_data;
	const Planet* m_parent;
};