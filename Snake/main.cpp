#include <iostream>
#include <string>
#include <list>

#include <GL\glew.h>
#include <SDL2\SDL.h>

#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "input.h"
#include "snake.h"
#include "apple.h"
#include "walls.h"

void SetUpGame();
void Game();
bool PlayAgain();

const Uint8 *keyState = SDL_GetKeyboardState(NULL);

GLuint uniforms[2];

Display window(800, 600, "SNAKE");

Shader shader("./res/basicShader", uniforms);

Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), 60.0f, 800.0f / 600.0f, 0.1f, -1000.0f);

Input input;

Snake snake;

Apple apple;

Walls walls(21.0f, 16.0f);

int oldTime = SDL_GetTicks();
int newTime = 0;

float deltaTime =	0.0f;
float startTimer =	5.0f;

int main(int argc, char ** argv) 
{
	window.Hide();

	SetUpGame();

	window.Show();

	while (!window.IsClosed())
	{
		if (!snake.GameOver()) 
		{
			newTime = SDL_GetTicks();
			deltaTime = float(newTime - oldTime) / 1000.0f;
			oldTime = newTime;

			window.Clear(0.0f, 0.0f, 0.0f, 1.0f);

			shader.Bind();

			Game();

			window.Update();
		}
		else 
		{
			window.Hide();

			if (PlayAgain()) 
			{
				SetUpGame();

				window.Show();
				snake.GameOver() = false;
				snake.Score() = 0;
			}
			else 
			{
				window.IsClosed() = true;
			}
		}
	}

	return 0;
}

void SetUpGame()
{
	std::string input = "";

	std::cout << "WELCOME TO SNAKE" << std::endl;

	do
	{
		std::cout << "DO YOU WANT WALLS (Y \\ N)" << std::endl;
		std::getline(std::cin, input);
		std::cout << std::endl;
	} 
	while ( input != "y" && 
			input != "Y" && 
			input != "n" && 
			input != "N");

	if (input == "y" || input == "Y") 
	{
		walls.IsActive() =		true;
		snake.WallsActive() =	true;
	}
	else 
	{
		walls.IsActive() =		false;
		snake.WallsActive() =	false;
	}

	std::cout << std::string(50, '\n') << std::endl;
}

void Game()
{
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		snake.Reset();
		snake.GameOver() = true;
	}

	input.Update();

	if (startTimer > 0.0f)
	{
		startTimer -= deltaTime;
	}
	else
	{
		snake.Controller(input);
		snake.Update(apple, deltaTime);
	}

	if (walls.IsActive())
	{
		walls.Draw(uniforms, camera);
	}

	snake.Draw(uniforms, camera);
	apple.Draw(uniforms, camera);
}

bool PlayAgain()
{
	std::string input = "";

	std::cout << "YOUR SCORE: " << snake.Score() << std::endl;

	do
	{
		std::cout << "WOULD YOU LIKE TO PLAY AGAIN? (Y \\ N)" << std::endl;
		std::getline(std::cin, input);
		std::cout << std::endl;

		std::cout << std::string(50, '\n') << std::endl;
	} 
	while ( input != "y" &&
			input != "Y" &&
			input != "n" &&
			input != "N");

	return ((input == "y" || input == "Y"));
}