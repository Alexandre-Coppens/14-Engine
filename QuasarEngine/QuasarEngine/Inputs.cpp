#include "Inputs.h"
#include "Time.h"
#include <SDL.h>

std::map<int, uint16_t>	Inputs::mKeyTime;
std::map<int, bool> Inputs::mKeyDown ;
std::map<int, bool> Inputs::mKeyHold;
std::map<int, bool> Inputs::mKeyUp;
bool Inputs::mEventQuit = false;

void Inputs::ComputeInputs()
{
	FlushLateInputs();

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
}

void Inputs::SortInput(SDL_Event& event)
{
	if (event.type != SDL_KEYDOWN && event.type != SDL_KEYUP) return;

	int key = event.key.keysym.sym;

	switch (event.type)
	{
	case SDL_KEYDOWN:
		if (mKeyTime[key] == 0)
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
