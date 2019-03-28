#include "snake.h"

Snake::Snake()
{
	m_wallsActive =		false;
	m_gameOver =		false;

	m_mesh = Mesh(m_verts, sizeof(m_verts));

	m_dir = m_right;

	m_blocks.push_back(m_front);
	m_blocks.push_back(m_middle);
	m_blocks.push_back(m_end);

	float pos = 0.0f;

	for (std::list<Block*>::iterator it = m_blocks.begin(); it != m_blocks.end(); it++)
	{
		(*it)->m_transform.SetPos(glm::vec3(pos, 0.0f, -2.5f));
		pos -= 1.0f;
	}
}

void Snake::Controller(Input &input)
{
	if (input.GetAxis("Horizontal") > 0.0f && input.GetAxis("Vertical") == 0.0f)
	{
		m_dir = m_right;
	}
	else if (input.GetAxis("Horizontal") < 0.0f  && input.GetAxis("Vertical") == 0.0f)
	{
		m_dir = m_left;
	}
	else if (input.GetAxis("Horizontal") == 0.0f && input.GetAxis("Vertical") > 0.0f)
	{
		m_dir = m_up;
	}
	else if (input.GetAxis("Horizontal") == 0.0f && input.GetAxis("Vertical") < 0.0f)
	{
		m_dir = m_down;
	}
	else 
	{
		m_dir = m_dir;
	}
}

void Snake::Update(Apple & apple, const float &deltaTime)
{
	m_updateTimer += deltaTime;

	if (m_updateTimer >= 0.1f)
	{
		// update positions
		for (std::list<Block*>::iterator it = m_blocks.begin(); it != m_blocks.end(); it++)
		{
			if (it == m_blocks.begin())
			{
				(*it)->m_oldPosition = (*it)->m_transform.GetPos();

				if (((*it)->m_transform.GetPos() + m_dir) == m_middle->m_transform.GetPos()) 
				{
					if (m_dir == m_left)
					{
						m_dir = m_right;
					}
					else if (m_dir == m_right) 
					{
						m_dir = m_left;
					}
					else if (m_dir == m_up)
					{
						m_dir = m_down;
					}
					else if (m_dir == m_down)
					{
						m_dir = m_up;
					}
				}

				(*it)->m_transform.GetPos() += m_dir;
			}
			else if (it == m_blocks.end())
			{
				(*it)->m_transform.GetPos() = (*m_it_copy)->m_oldPosition;
			}
			else
			{
				(*it)->m_oldPosition = (*it)->m_transform.GetPos();

				m_it_copy = it;
				m_it_copy--;

				(*it)->m_transform.GetPos() = (*m_it_copy)->m_oldPosition;
			}
		}

		m_updateTimer = 0.0f;
	}

	// check for collisions
	for (std::list<Block*>::iterator it = m_blocks.begin(); it != m_blocks.end(); it++)
	{
		if (it != m_blocks.begin())
		{
			if ((*it)->m_transform.GetPos() == (*m_blocks.begin())->m_transform.GetPos()) 
			{
				Reset();
				it = m_blocks.end();
				it--;
			}
		}
	}

	if (m_front->m_transform.GetPos() == apple.GetTransform().GetPos())
	{
		AddBlock();
		apple.GetNewPos();
	}

	if (m_wallsActive) 
	{
		if (m_front->m_transform.GetPos().x == MAX_X)
		{
			Reset();
		}
		else if (m_front->m_transform.GetPos().x == -MAX_X)
		{
			Reset();
		}

		if (m_front->m_transform.GetPos().y == MAX_Y)
		{
			Reset();
		}
		else if (m_front->m_transform.GetPos().y == -MAX_Y)
		{
			Reset();
		}
	}
	else
	{
		if (m_front->m_transform.GetPos().x > MAX_X)
		{
			m_front->m_transform.GetPos().x = -MAX_X;
		}
		else if (m_front->m_transform.GetPos().x < -MAX_X)
		{
			m_front->m_transform.GetPos().x = MAX_X;
		}

		if (m_front->m_transform.GetPos().y > MAX_Y)
		{
			m_front->m_transform.GetPos().y = -MAX_Y;
		}
		else if (m_front->m_transform.GetPos().y < -MAX_Y)
		{
			m_front->m_transform.GetPos().y = MAX_Y;
		}
	}
}

void Snake::Draw(GLuint * uniforms, Camera & camera)
{
	for (std::list<Block*>::iterator it = m_blocks.begin(); it != m_blocks.end(); it++)
	{
		m_mesh.Draw(uniforms, (*it)->m_transform, camera, m_color);
	}
}

void Snake::AddBlock()
{
	m_it_end = m_blocks.end();
	m_it_end--;

	m_newPos = glm::vec3((*m_it_end)->m_transform.GetPos().x,
						 (*m_it_end)->m_transform.GetPos().y,
						 (*m_it_end)->m_transform.GetPos().z);

	if (m_dir == m_left)
	{
		m_newPos.x -= 1.0f;
		m_blocks.push_back(new Block(m_newPos));
	}
	else if (m_dir == m_right)
	{
		m_newPos.x += 1.0f;
		m_blocks.push_back(new Block(m_newPos));
	}
	else if (m_dir == m_up)
	{
		m_newPos.y -= 1.0f;
		m_blocks.push_back(new Block(m_newPos));
	}
	else if (m_dir == m_down)
	{
		m_newPos.y += 1.0f;
		m_blocks.push_back(new Block(m_newPos));
	}

	m_score += 10;
}

void Snake::Reset()
{
	for (std::list<Block*>::iterator it = m_blocks.begin(); it != m_blocks.end(); it++)
	{
		if ((*it) != m_front && (*it) != m_middle && (*it) != m_end)
		{
			delete((*it));
		}
	}

	m_blocks.clear();

	m_blocks.push_back(m_front);
	m_blocks.push_back(m_middle);
	m_blocks.push_back(m_end);

	float pos = 0.0f;

	if (m_dir == m_right) 
	{
		for (std::list<Block*>::iterator it = m_blocks.begin(); it != m_blocks.end(); it++)
		{
			(*it)->m_transform.SetPos(glm::vec3(pos, m_front->m_transform.GetPos().y, m_front->m_transform.GetPos().z));
			pos -= 1.0f;
		}
	}
	else if (m_dir == m_left) 
	{
		for (std::list<Block*>::iterator it = m_blocks.begin(); it != m_blocks.end(); it++)
		{
			(*it)->m_transform.SetPos(glm::vec3(pos, m_front->m_transform.GetPos().y, m_front->m_transform.GetPos().z));
			pos += 1.0f;
		}
	}
	else if (m_dir == m_up)
	{
		for (std::list<Block*>::iterator it = m_blocks.begin(); it != m_blocks.end(); it++)
		{
			(*it)->m_transform.SetPos(glm::vec3(m_front->m_transform.GetPos().x, pos, m_front->m_transform.GetPos().z));
			pos -= 1.0f;
		}
	}
	else if (m_dir == m_down)
	{
		for (std::list<Block*>::iterator it = m_blocks.begin(); it != m_blocks.end(); it++)
		{
			(*it)->m_transform.SetPos(glm::vec3(m_front->m_transform.GetPos().x, pos, m_front->m_transform.GetPos().z));
			pos += 1.0f;
		}
	}

	m_gameOver = true;
}
