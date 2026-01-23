#pragma once
#include <SDL_Image.h>
#include "Window.h"

#include "Rectangle.h"

class Sprite2D;
class Actor;
class Texture;
class Renderer
{
private:
	SDL_Renderer* pSDLRenderer;
public:
	SDL_Renderer* GetSdlRenderer() { return pSDLRenderer; }

	enum class Flip
	{
		None = SDL_FLIP_NONE,
		Horizontal = SDL_FLIP_HORIZONTAL,
		Vertical = SDL_FLIP_VERTICAL
	};

private:
	void DrawSprites();
	void DrawSprite(const Actor&, const Texture&, Rectangle, Vector2, Flip) const;

public:
	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator= (const Renderer&) = delete;

	bool Initialize(Window& _pWindow);
	void BeginDraw();
	void EndDraw();
	void Close();

	void Draw();
	void AddSprite(Sprite2D* sprite);
	void RemoveSprite(Sprite2D* sprite);
};