#pragma once
#include <SDL_rect.h>
#include "Engine/Utilitaries/CommonLib.h"

struct Rectangle
{
	Vector2 position;
	Vector2 size;

	Rectangle():position(Vector2Zero()), size(Vector2Zero()){}
	Rectangle(Vector2 _pos, Vector2 _size) : position(_pos), size(_size) {}
	Rectangle(float _posX, float _posY, float _sizeX, float _sizeY) : position(_posX, _posY), size(_sizeX, _sizeY) {}

	SDL_Rect ToSDLRect() const
	{
		return SDL_Rect{
			static_cast<int>(position.x),
			static_cast<int>(position.y),
			static_cast<int>(size.x),
			static_cast<int>(size.y) };
	}
};

