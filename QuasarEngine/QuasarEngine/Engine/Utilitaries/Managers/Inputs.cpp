#include "Inputs.h"
#include "Engine/Utilitaries/Time.h"
#include <SDL.h>

#include "ImguiManager.h"

std::map<int, float>Inputs::mKeyTime;
std::map<int, bool> Inputs::mKeyDown ;
std::map<int, bool> Inputs::mKeyHold;
std::map<int, bool> Inputs::mKeyUp;
std::map<int, float>Inputs::mMouseTime;
std::map<int, bool> Inputs::mMouseDown ;
std::map<int, bool> Inputs::mMouseHold;
std::map<int, bool> Inputs::mMouseUp;
bool Inputs::mEventQuit = false;
int Inputs::mMouseDeltaX = 0;
int Inputs::mMouseDeltaY = 0;
bool Inputs::getMouse {true};

void Inputs::ComputeInputs()
{
	FlushLateInputs();
	if (getMouse)
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_GetRelativeMouseState(&mMouseDeltaX, &mMouseDeltaY);
	}
	else
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
		mMouseDeltaX = 0;
		mMouseDeltaY = 0;
	}
	
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mEventQuit = true;
			break;
		default:
			SortInput(event);
			break;
		}
	}
	ImguiManager::PullEvents(&event);
}

void Inputs::SortInput(const SDL_Event& _event)
{
	if (_event.type != SDL_KEYDOWN && _event.type != SDL_KEYUP) return;

	int key = _event.key.keysym.sym;
	int button = _event.button.button;

	if (key == SDLK_F4 && GetKey(SDLK_LCTRL)) mEventQuit = true;
	if (key == SDLK_ESCAPE && !GetKey(SDLK_ESCAPE)) getMouse = !getMouse;
	
	switch (_event.type)
	{
	case SDL_KEYDOWN:
		if (mKeyTime[key] == 0.0f)
		{
			mKeyTime[key] = Time::currentFrameTime;
			mKeyDown[key] = true;
		}
		break;
	case SDL_KEYUP:
		mKeyDown[key] = false;
		mKeyHold[key] = false;
		mKeyUp[key] = true;
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (mMouseTime[button] == 0.0f)
		{
			mMouseTime[button] = Time::currentFrameTime;
			mMouseDown[button] = true;
		}
		break;

	case SDL_MOUSEBUTTONUP:
		mMouseDown[button] = false;
		mMouseHold[button] = false;
		mMouseUp[button] = true;
		break;
		
	default:
		break;
	}
}

void Inputs::FlushLateInputs()
{
	for (auto const& [key, val] : mKeyTime)
	{
		if (mKeyDown[key])
		{
			mKeyDown[key] = false;
			mKeyHold[key] = true;
		}
		if (mKeyUp[key])
		{
			mKeyTime[key] = 0;
			mKeyUp[key] = false;
		}
	}
	for (auto const& [key, val] : mMouseTime)
	{
		if (mMouseDown[key])
		{
			mMouseDown[key] = false;
			mMouseHold[key] = true;
		}
		if (mMouseUp[key])
		{
			mMouseTime[key] = 0;
			mMouseUp[key] = false;
		}
	}
}

bool Inputs::GetKey(int key)
{
	return (mKeyDown[key] || mKeyHold[key]);
}

bool Inputs::GetKeyDown(int key)
{
	return mKeyDown[key];
}

bool Inputs::GetKeyHold(int key)
{
	return mKeyHold[key];
}

bool Inputs::GetKeyUp(int key)
{
	return mKeyUp[key];
}

bool Inputs::GetMouseDown(MouseButton _button)
{
	return mMouseDown[_button];
}

bool Inputs::GetMouseHold(MouseButton _button)
{
	return mMouseHold[_button];
}

bool Inputs::GetMouseUp(MouseButton _button)
{
	return mMouseUp[_button];
}
