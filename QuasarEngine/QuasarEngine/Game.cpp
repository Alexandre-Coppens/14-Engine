#include <SDL.h>
#include "Game.h"
#include "Time.h"
#include "Inputs.h"

#include "Scene.h"

Game::Game(std::string _title, std::vector<Scene*> _scenes):
	mIsRunning(true), mTitle(_title), mScenes(_scenes)
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

	for (Scene* s : mScenes) s->setRenderer(pRenderer);
}

Game::~Game()
{
}

void Game::Initialize()
{
	pWindow = new Window(800, 800, mTitle);

	if (pWindow->Open() && pRenderer->Initialize(*pWindow))
	{
		mScenes[mCurrentScene] -> Load();
		Loop();
	}
}

void Game::Loop()
{
	while (mIsRunning)
	{
		Time::ComputeDeltaTime();

		mScenes[mCurrentScene]->EarlyUpdate();
		Inputs::ComputeInputs();

		mScenes[mCurrentScene]->Update(Time::deltaTime);

		Render();
		mScenes[mCurrentScene]->LateUpdate();

		Inputs::FlushLateInputs();
		mIsRunning = !Inputs::GetEventQuit();
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
	for (Scene* scene : mScenes)
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