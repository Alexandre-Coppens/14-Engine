#include <SDL.h>
#include "Game.h"
#include "Time.h"
#include "Inputs.h"
#include "Assets.h"

#include "Scene.h"
#include "RendererSdl.h"
#include "RendererGl.h"

Game::Game(std::string _title, std::vector<Scene*> _scenes, RendererType _rendererType):
	mTitle(std::move(_title)), mScenes(std::move(_scenes))
{ //TODO: Remove Scenes vector from init to put it in the game
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_Log("SDL initialization failed. SDL Error: %s", SDL_GetError());
	}
	else
	{
		SDL_Log("SDL initialization succeeded");
	}

	switch (_rendererType)
	{
	case RendererType::SDL:
		pRenderer = new RendererSdl();
		break;

	case RendererType::OPENGL:
		pRenderer = new RendererGl();
		break;
	}

	for (Scene* s : mScenes) s->setRenderer(pRenderer);
}

Game::~Game()
{
	Assets::Clear();
}

void Game::Initialize()
{
	Log::Info("GAME: Initializing " + mTitle);
	pWindow = new Window(Window::GetSize().x, Window::GetSize().y, mTitle);

	if (pWindow->Open() && pRenderer->Initialize(*pWindow))
	{
		mScenes[mCurrentScene] -> Load(this);
	}
}

void Game::Loop()
{
	while (!Inputs::GetEventQuit())
	{
		Time::ComputeDeltaTime();

		mScenes[mCurrentScene]->EarlyUpdate();
		Inputs::ComputeInputs();

		mScenes[mCurrentScene]->Update(Time::deltaTime);

		Render();
		mScenes[mCurrentScene]->LateUpdate();

		Time::DelayTime();
	}
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
		scene->Close();
		delete scene;
		scene = nullptr;
	}

	pRenderer->Close();
	delete pRenderer;
	pRenderer = nullptr;

	pWindow->Close();
	delete pWindow;
	pWindow = nullptr;
}

