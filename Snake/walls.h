#pragma once

#include <glm\glm.hpp>
#include "transform.h"
#include "mesh.h"

class Walls 
{
public:
	Walls(const float &maxX, const float &maxY);

	void Draw(GLuint *uniforms, Camera &camera);

	inline bool &IsActive() { return m_isActive; }

private:
	const float m_verts[18]
	{
		 0.5f, 0.5f, 0.0f,
		 0.5f,-0.5f, 0.0f,
		-0.5f,-0.5f, 0.0f,

		 0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f,-0.5f, 0.0f,
	};

	bool m_isActive;

	Transform m_transform[4];

	Mesh m_mesh;

	glm::vec3 m_color = glm::vec3(1.0f, 1.0f, 1.0f);
};