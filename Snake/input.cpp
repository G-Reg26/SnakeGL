#include "input.h"

Input::Input()
{
}

float Input::GetAxis(const std::string axis)
{
	if (axis == "Horizontal") 
	{
		return m_horizontalAxis;
	}

	if (axis == "Vertical") 
	{
		return m_verticalAxis;
	}

	return 0.0f;
}

void Input::Update()
{
	m_horizontalAxis =	0;
	m_verticalAxis =	0;

	if (m_keyState[SDL_SCANCODE_D])
	{
		m_horizontalAxis = 1.0;
	}
	
	if (m_keyState[SDL_SCANCODE_A])
	{
		m_horizontalAxis = -1.0;
	}

	if (m_keyState[SDL_SCANCODE_W])
	{
		m_verticalAxis = 1.0;
	}

	if (m_keyState[SDL_SCANCODE_S])
	{
		m_verticalAxis = -1.0;
	}
}
