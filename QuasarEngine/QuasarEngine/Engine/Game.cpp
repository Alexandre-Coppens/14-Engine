#include <SDL.h>
#include "Game.h"

#include "Engine/Utilitaries/Time.h"
#include "Engine/Utilitaries/Log.h"
#include "Engine/Utilitaries/Managers/Inputs.h"
#include "Engine/Utilitaries/Assets.h"
#include "Utilitaries/DebugMemoryLeakCatcher.h"

#include "Engine/Render/RendererSdl.h"
#include "Engine/Render/RendererGl.h"

#include "Engine/Scene.h"
#include "Utilitaries/Managers/ImguiManager.h"

Game::Game(std::string _title, std::vector<Scene*> _scenes, RendererType _rendererType):
	mTitle(std::move(_title)), mScenes(std::move(_scenes))
{ //TODO: Remove Scenes vector from init to put it in the game
	DEBUGAddClass("Game");
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
		mRenderer = new RendererSdl();
		break;

	case RendererType::OPENGL:
		mRenderer = new RendererGl();
		break;
	}
}

Game::~Game() = default;

void Game::Initialize()
{
	Log::Info("GAME: Initializing " + mTitle);
	mWindow = new Window(static_cast<Uint16>(Window::GetSize().x), static_cast<Uint16>(Window::GetSize().y), mTitle);

	Assets::setRenderer(mRenderer);
	if (mWindow->Open() && mRenderer->Initialize(*mWindow))
	{
		mScenes[0]->setRenderer(mRenderer);
		mScenes[0]->Open(this);
	}
	
	ImguiManager::Initialize(mRenderer, mWindow);
}

void Game::Loop()
{
	while (!Inputs::GetEventQuit())
	{
		Time::ComputeDeltaTime();
		
		mScenes[mCurrentScene]->EarlyUpdate();
		Inputs::ComputeInputs();

		mScenes[mCurrentScene]->Update(Time::deltaTime);
		ImguiManager::Update();

		Render();
		mScenes[mCurrentScene]->LateUpdate();

		Time::DelayTime();
		if (mChangeSceneTo != -1) ChangeScene();
	}
}

void Game::Render()
{
	mRenderer->BeginDraw();
	mRenderer->Draw();
	ImguiManager::Render();
	mRenderer->EndDraw();
}

void Game::Close()
{
	ImguiManager::Close();
	for (Scene* scene : mScenes)
	{
		scene->Close();
		delete scene;
		scene = nullptr;
	}
	mScenes.clear();
	
	mRenderer->Close();
	delete mRenderer;
	mRenderer = nullptr;

	mWindow->Close();
	delete mWindow;
	mWindow = nullptr;
	
	Assets::Clear();
	DEBUGRemoveClass("Game");
}

