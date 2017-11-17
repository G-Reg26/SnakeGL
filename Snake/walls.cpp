#include "walls.h"

Walls::Walls(const float & maxX, const float & maxY)
{
	m_isActive = false;

	m_mesh = Mesh(m_verts, sizeof(m_verts));

	m_transform[0].SetPos(glm::vec3(-maxX, 0.0f, -2.5f));
	m_transform[1].SetPos(glm::vec3( maxX, 0.0f, -2.5f));
	m_transform[2].SetPos(glm::vec3( 0.0f,-maxY, -2.5f));
	m_transform[3].SetPos(glm::vec3( 0.0f, maxY, -2.5f));

	m_transform[0].SetScale(glm::vec3(1.0f, (2 * maxY), 1.0f));
	m_transform[1].SetScale(glm::vec3(1.0f, (2 * maxY), 1.0f));
	m_transform[2].SetScale(glm::vec3((2 * maxX), 1.0f, 1.0f));
	m_transform[3].SetScale(glm::vec3((2 * maxX), 1.0f, 1.0f));
}

void Walls::Draw(GLuint * uniforms, Camera & camera)
{
	for (int i = 0; i < sizeof(m_transform) / sizeof(m_transform[0]); i++) 
	{
		m_mesh.Draw(uniforms, m_transform[i], camera, m_color);
	}
}
