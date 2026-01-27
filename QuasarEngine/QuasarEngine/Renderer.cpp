#include "Renderer.h"
#include "MathLib.h"

#include "Log.h"
#include "Actor.h"
#include "Texture.h"
#include "cSprite2D.h"


Renderer::Renderer() :
	pSDLRenderer(nullptr)
{
}

bool Renderer::Initialize(Window& _pWindow)
{
	pSDLRenderer = SDL_CreateRenderer(_pWindow.GetSdlWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!pSDLRenderer)
	{
		Log::Error(LogType::Video, "Failed to create Renderer");
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		Log::Error(LogType::Video, "Unable to initialize SDL_Image");
		return false;
	}
	return true;
}

void Renderer::BeginDraw()
{
	SDL_SetRenderDrawColor(pSDLRenderer, 120, 120, 255, 255);
	SDL_RenderClear(pSDLRenderer);
}

void Renderer::EndDraw()
{
	SDL_RenderPresent(pSDLRenderer);
}

void Renderer::Close()
{
	SDL_DestroyRenderer(pSDLRenderer);
}

void Renderer::Draw()
{
	DrawSprites();
}

void Renderer::DrawSprites()
{
	for (Sprite2D* sprite : vSpriteList)
	{
		sprite->Draw(*this);
	}
}

void Renderer::DrawSprite(Actor& _pActor, const Texture& _pTex, Rectangle _SourceRect, Vector2 _v2Size, Vector2 _v2Origin, Flip _Flip) const
{
	SDL_Rect destinationRect;
	Transform2D transform = *_pActor.GetTransform();
	destinationRect.w = static_cast<int>(_v2Size.x * transform.GetScale().x);
	destinationRect.h = static_cast<int>(_v2Size.y * transform.GetScale().y);
	destinationRect.x = static_cast<int>(transform.GetLocation().x - ( _v2Size.x * _v2Origin.x));
	destinationRect.y = static_cast<int>(transform.GetLocation().y - (_v2Size.y * _v2Origin.y));

	SDL_Rect* sourceSDL = nullptr;
	if (Equal(_SourceRect.dimensions, Vector2Zero())) //WTF IS RECTANGLE::NULLRECT SERIOUSLY
	{
		sourceSDL = new SDL_Rect{
			Round(0),
			Round(0),
			Round(_pTex.GetWidth()),
			Round(_pTex.GetHeight()) };
	}
	else
	{
		sourceSDL = new SDL_Rect{
			Round(_SourceRect.position.x),
			Round(_SourceRect.position.y),
			Round(_SourceRect.dimensions.x),
			Round(_SourceRect.dimensions.y) };
	}

	SDL_RenderCopyEx(
		pSDLRenderer,
		_pTex.GetSdlTexture(),
		sourceSDL,
		&destinationRect,
		-ToDeg(transform.GetRotation()),
		nullptr,
		SDL_FLIP_NONE);

	delete sourceSDL;
}

void Renderer::AddSprite(Sprite2D* pSprite)
{
	int spriteDrawOrder = pSprite->GetDrawOrder();
	std::vector<Sprite2D*>::iterator s2D;
	for (s2D = vSpriteList.begin(); s2D != vSpriteList.end(); s2D++)
	{
		if (spriteDrawOrder < (*s2D)->GetDrawOrder()) break;
	}
	vSpriteList.insert(s2D, pSprite);
}

void Renderer::RemoveSprite(Sprite2D* pSprite)
{
	std::vector<Sprite2D*>::iterator s2D;
	s2D = std::find(vSpriteList.begin(), vSpriteList.end(), pSprite);
	vSpriteList.erase(s2D);
}
