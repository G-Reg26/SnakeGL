#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "mesh.h"
#include "transform.h"
#include "camera.h"

class Apple 
{
public:
	Apple();

	void Draw(GLuint *uniforms, Camera &camera);

	void GetNewPos();

	inline Transform & GetTransform() { return m_transform; }

private:
	const int MAX_X = 20;
	const int MAX_Y = 15;

	const float m_verts[18]
	{
		 0.5f, 0.5f, 0.0f,
		 0.5f,-0.5f, 0.0f,
		-0.5f,-0.5f, 0.0f,

		 0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f,-0.5f, 0.0f,
	};

	Mesh m_mesh;

	Transform m_transform;

	glm::vec3 m_oldPosition =	glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 m_color =			glm::vec3(1.0f, 0.0f, 0.0f);
};
