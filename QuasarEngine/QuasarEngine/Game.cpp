#include <SDL.h>
#include "Game.h"


Game::Game(std::string _sTitle):
	bIsRunning(true), sTitle(_sTitle)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_Log("SDL initialization failed. SDL Error: %s", SDL_GetError());
	}
	else
	{
		SDL_Log("SDL initialization succeeded!");
	}
	Initialize();
}

Game::~Game()
{

}

void Game::Initialize()
{
	pWindow = new Window(800, 800, sTitle);
	if (pWindow->Open()) Loop();
}

void Game::Loop()
{
	CheckInputs();
	Update();
	Render();
}

void Game::Render()
{
}

void Game::Update()
{
}

void Game::CheckInputs()
{
	if (bIsRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				bIsRunning = false;
				break;
			default:
				//SendInputs
				break;
			}
		}
	}
}

void Game::Close()
{
	pWindow->Close();
}