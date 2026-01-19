#pragma once
#include <SDL_rect.h>
#include "CommonLib.h"

struct Rectangle
{
	Vector2 position;
	Vector2 dimensions;

	SDL_Rect ToSDLRect() const
	{
		return SDL_Rect{
			static_cast<int>(position.x),
			static_cast<int>(position.y),
			static_cast<int>(dimensions.x),
			static_cast<int>(dimensions.y) };
	}
};