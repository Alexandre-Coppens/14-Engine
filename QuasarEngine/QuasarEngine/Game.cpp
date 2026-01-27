#include <SDL.h>
#include "Game.h"
#include "Time.h"
#include "Inputs.h"

#include "Scene.h"

Game::Game(std::string _sTitle, std::vector<Scene*> _vScenes):
	bIsRunning(true), sTitle(_sTitle), vScenes(_vScenes)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_Log("SDL initialization failed. SDL Error: %s", SDL_GetError());
	}
	else
	{
		SDL_Log("SDL initialization succeeded");
	}
	pRenderer = new Renderer();

	for (Scene* s : vScenes) s->SetRenderer(pRenderer);
}

Game::~Game()
{
}

void Game::Initialize()
{
	pWindow = new Window(800, 800, sTitle);

	if (pWindow->Open() && pRenderer->Initialize(*pWindow))
	{
		vScenes[u8CurrentScene] -> Load();
		Loop();
	}
}

void Game::Loop()
{
	while (bIsRunning)
	{
		Time::ComputeDeltaTime();

		vScenes[u8CurrentScene]->EarlyUpdate();
		Inputs::ComputeInputs();

		vScenes[u8CurrentScene]->Update(Time::deltaTime);

		Render();
		vScenes[u8CurrentScene]->LateUpdate();

		Inputs::FlushLateInputs();
		bIsRunning = !Inputs::GetEventQuit();
		Time::DelayTime();
	}
	Close();
}

void Game::Render()
{
	pRenderer->BeginDraw();
	pRenderer->Draw();
	pRenderer->EndDraw();
}

void Game::Close()
{
	for (Scene* scene : vScenes)
	{
		delete scene;
	}

	pRenderer->Close();
	delete pRenderer;
	pRenderer = nullptr;

	pWindow->Close();
	delete pWindow;
	pWindow = nullptr;
}