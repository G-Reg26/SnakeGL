#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <GL\glew.h>

class Shader
{
public:
	enum Uniforms {
		TRANSFORM,
		TEX_OFF,
		COLOR_OFF,
		TEX_OR_COLOR,
		UNIFORMS
	};

	GLuint m_uniforms[UNIFORMS];

	Shader(const std::string& fileName, GLuint * uniforms);

	void Bind();

	inline GLuint GetProgram() { return m_program; };

	virtual ~Shader();

private:
	static const unsigned int NUM_SHADERS = 2;

	GLuint m_program;
	GLuint m_shader[NUM_SHADERS];
};

