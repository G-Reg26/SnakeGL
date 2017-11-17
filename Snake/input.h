#pragma once

#include <SDL2\SDL.h>
#include <string>
#include <iostream>

class Input
{
public:
	Input();

	float GetAxis(const std::string axis);

	void Update();

private:
	const Uint8 *m_keyState = SDL_GetKeyboardState(NULL);

	float m_horizontalAxis =	0.0;
	float m_verticalAxis =		0.0;
};

