#pragma once
#include "Window.h"

enum class Flip
{
	None = SDL_FLIP_NONE,
	Horizontal = SDL_FLIP_HORIZONTAL,
	Vertical = SDL_FLIP_VERTICAL
};

enum class RendererType
{
	SDL,
	OPENGL
};

enum class DebugMode
{
	NONE,
	DRAW_COLLISIONS
};

class Sprite2D;
class Texture;
class IRenderer
{
public:
	virtual ~IRenderer() = default;

	virtual bool Initialize(Window& _rWindow) = 0;
	virtual void BeginDraw() = 0;
	virtual void Draw() = 0;
	virtual void EndDraw() = 0;
	virtual void Close() = 0;
	virtual RendererType getType() = 0;
};