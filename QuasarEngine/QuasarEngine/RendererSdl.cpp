#include "RendererSdl.h"
#include "MathLib.h"

#include "Log.h"
#include "Actor.h"
#include "Texture.h"
#include "cSprite2D.h"
#include "Rectangle.h"

RendererSdl::RendererSdl() :
	pSDLRenderer(nullptr)
{
}

bool RendererSdl::Initialize(Window& _pWindow)
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

void RendererSdl::BeginDraw()
{
	SDL_SetRenderDrawColor(pSDLRenderer, 120, 120, 255, 255);
	SDL_RenderClear(pSDLRenderer);
}

void RendererSdl::EndDraw()
{
	SDL_RenderPresent(pSDLRenderer);
}

void RendererSdl::Close()
{
	SDL_DestroyRenderer(pSDLRenderer);
}

void RendererSdl::Draw()
{
	DrawSprites();
}

void RendererSdl::DrawSprites()
{
	if (mSpriteList.empty()) return;
	for (Sprite2D* sprite : mSpriteList)
	{
		sprite->Draw(*this, DebugMode::DRAW_COLLISIONS);
	}
}

void RendererSdl::DrawSprite(Actor& _pActor, const Texture* _pTex, const Rectangle& _sourceRect, const Vector2 _origin, Flip _flip) const
{
	SDL_Rect destinationRect;
	const Transform2D transform = *_pActor.getTransform2D();
	destinationRect.w = static_cast<int>(transform.getSize().x * transform.getScale().x);
	destinationRect.h = static_cast<int>(transform.getSize().y * transform.getScale().y);
	destinationRect.x = static_cast<int>(transform.getLocation().x - (transform.getSize().x * _origin.x));
	destinationRect.y = static_cast<int>(transform.getLocation().y - (transform.getSize().y * _origin.y));

	const SDL_Rect* sourceSDL;
	if (Equal(_sourceRect.size, Vector2Zero()))
	{
		sourceSDL = new SDL_Rect{
			Round(0),
			Round(0),
			Round(_pTex->GetWidth()),
			Round(_pTex->GetHeight()) };
	}
	else
	{
		sourceSDL = new SDL_Rect{
			Round(_sourceRect.position.x),
			Round(_sourceRect.position.y),
			Round(_sourceRect.size.x),
			Round(_sourceRect.size.y) };
	}

	SDL_RenderCopyEx(
		pSDLRenderer,
		_pTex->GetSdlTexture(),
		sourceSDL,
		&destinationRect,
		-ToDeg(transform.getRotation()),
		nullptr,
		static_cast<SDL_RendererFlip>(_flip));

	delete sourceSDL;
}

void RendererSdl::AddSprite(Sprite2D* _pSprite)
{
	int spriteDrawOrder = _pSprite->getDrawOrder();
	std::vector<Sprite2D*>::iterator s2D;
	for (s2D = mSpriteList.begin(); s2D != mSpriteList.end(); s2D++)
	{
		if (spriteDrawOrder < (*s2D)->getDrawOrder()) break;
	}
	mSpriteList.insert(s2D, _pSprite);
}

void RendererSdl::RemoveSprite(const Sprite2D* _pSprite)
{
	std::vector<Sprite2D*>::iterator s2D;
	s2D = std::find(mSpriteList.begin(), mSpriteList.end(), _pSprite);
	if (s2D == mSpriteList.end()) return;
	mSpriteList.erase(s2D);
}

void RendererSdl::DrawDebugBox(const Rectangle& _rect, const Vector2 _origin) const
{
	SDL_SetRenderDrawColor(pSDLRenderer, 0, 255, 0, 255);
	const SDL_Rect* sourceSDL = new SDL_Rect{
			Round(_rect.position.x - (_rect.size.x * _origin.x)),
			Round(_rect.position.y - (_rect.size.y * _origin.y)),
			Round(_rect.size.x),
			Round(_rect.size.y) };

	SDL_RenderDrawRect(pSDLRenderer, sourceSDL);
	delete sourceSDL;
}
