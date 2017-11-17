#pragma once

#include <list>
#include <SDL2\SDL.h>
#include<GL\glew.h>
#include <glm\glm.hpp>

#include "mesh.h"
#include "transform.h"
#include "camera.h"
#include "input.h"
#include "apple.h"

struct Block 
{
	Block(){}

	Block(glm::vec3 pos) 
	{
		m_transform.SetPos(pos);
	}

	Transform m_transform;

	glm::vec3 m_oldPosition;
};

class Snake 
{
public:
	Snake();

	void Controller(Input &input);
	void Update(Apple &apple, const float &deltaTime);
	void Draw(GLuint *uniforms, Camera &camera);

	void AddBlock();
	void Reset();

	inline bool &WallsActive()  { return m_wallsActive; }
	inline bool &GameOver()		{ return m_gameOver;	}
	inline int &Score()			{ return m_score;		}

	const int MAX_X = 21;
	const int MAX_Y = 16;

private:
	int m_score = 0;

	float m_updateTimer = 0.0f;
	bool m_wallsActive;
	bool m_gameOver;
	
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

	Block * m_front =	new Block;
	Block * m_middle =	new Block;
	Block * m_end =		new Block;

	std::list<Block*> m_blocks;

	glm::vec3 m_up =		glm::vec3( 0.0f, 1.0f, 0.0f);
	glm::vec3 m_down =		glm::vec3( 0.0f,-1.0f, 0.0f);
	glm::vec3 m_right =		glm::vec3( 1.0f, 0.0f, 0.0f);
	glm::vec3 m_left =		glm::vec3(-1.0f, 0.0f, 0.0f);

	glm::vec3 m_dir =		glm::vec3( 0.0f, 0.0f, 0.0f);
	glm::vec3 m_newPos =	glm::vec3( 0.0f, 0.0f, 0.0f);

	glm::vec3 m_color =		glm::vec3( 0.0f, 1.0f, 0.0f);

	std::list<Block*>::iterator m_it_copy;
	std::list<Block*>::iterator m_it_end;
};