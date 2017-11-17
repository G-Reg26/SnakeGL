#pragma once

#include <iostream>
#include <string.h>
#include <SDL2\SDL.h>

#include "camera.h"
#undef main

class Display {
public:
	Display(int width, int height, const std::string title);
	
	void Update();
	void Clear(float r, float g, float b, float a);
	void Resize();
	void Raise();
	void Hide();
	void Show();
	
	inline bool &IsClosed()		 { return m_isClosed; }
	inline SDL_Event &GetEvent() { return m_e;		  }

	virtual ~Display();
private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	SDL_Event m_e;

	int m_width;
	int m_height;
	bool m_isClosed;
};