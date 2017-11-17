#pragma once

#include <iostream>
#include <string.h>
#include <GL\glew.h>
#include <glm\glm.hpp>

#include "transform.h"
#include "camera.h"
#include "shader.h"

class Mesh
{
public:;

	Mesh(const float * verticies, const unsigned int vertSize);
	Mesh() {}
	
	void Draw(const GLuint * uniform, const Transform& transform, const Camera& camera, glm::vec3 &color);

	virtual ~Mesh();
private:

	GLuint m_positionBufferObject;
};

