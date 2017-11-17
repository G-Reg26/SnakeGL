#include "apple.h"

Apple::Apple()
{
	m_transform.GetPos().x = (float)((rand() % (MAX_X * 2) + 1) - MAX_X);
	m_transform.GetPos().y = (float)((rand() % (MAX_Y * 2) + 1) - MAX_Y);
	m_transform.GetPos().z = -2.5f;

	m_mesh = Mesh(m_verts, sizeof(m_verts));
}

void Apple::Draw(GLuint * uniforms, Camera & camera)
{
	m_mesh.Draw(uniforms, m_transform, camera, m_color);
}

void Apple::GetNewPos()
{
	m_oldPosition = m_transform.GetPos();

	while (m_oldPosition == m_transform.GetPos())
	{
		m_transform.GetPos().x = (float)((rand() % (MAX_X * 2) + 1) - MAX_X);
		m_transform.GetPos().y = (float)((rand() % (MAX_Y * 2) + 1) - MAX_Y);
	}
}
