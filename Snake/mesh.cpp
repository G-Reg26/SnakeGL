#include "mesh.h"

Mesh::Mesh(const float * verticies, const unsigned int vertSize)
{
	glGenBuffers(1, &m_positionBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, m_positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vertSize, verticies, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::Draw(const GLuint * uniforms, const Transform& transform, const Camera& camera, glm::vec3 &color)
{
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();

	glUniformMatrix4fv(uniforms[0], 1, GL_FALSE, &model[0][0]);
	glUniform3f(uniforms[1], color.x, color.y, color.z);

	glBindBuffer(GL_ARRAY_BUFFER, m_positionBufferObject);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	glDisableVertexAttribArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_positionBufferObject);
}
