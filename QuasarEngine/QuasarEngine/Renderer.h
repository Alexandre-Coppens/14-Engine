#pragma once
#include <SDL_Image.h>
#include "Window.h"

#include "Rectangle.h"
#include <vector>

class Sprite2D;
class Actor;
class Texture;
class Renderer
{
private:
	SDL_Renderer* pSDLRenderer;
	std::vector<Sprite2D*> mSpriteList = {};
public:
	SDL_Renderer* getSdlRenderer() { return pSDLRenderer; }

	enum class Flip
	{
		None = SDL_FLIP_NONE,
		Horizontal = SDL_FLIP_HORIZONTAL,
		Vertical = SDL_FLIP_VERTICAL
	};

private:

public:
	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator= (const Renderer&) = delete;

	bool Initialize(Window& _pWindow);
	void BeginDraw();
	void EndDraw();
	void Close();

	void Draw();
	void DrawSprites();
	void DrawSprite(Actor& _pActor, const Texture& _pTex, Rectangle _SourceRect, Vector2 _v2Size, Vector2 _v2Origin, Flip _Flip) const;

	void AddSprite(Sprite2D* sprite);
	void RemoveSprite(Sprite2D* sprite);
};