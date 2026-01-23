#include "Renderer.h"
#include "Log.h"

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
	/*SDL_SetRenderDrawColor(pSDLRenderer, 255, 255, 255, 255);
	SDL_Rect sdlRect = _pRect.ToSDLRect();
	SDL_RenderFillRect(pSDLRenderer, &sdlRect);*/
}

void Renderer::DrawSprite(const Actor&, const Texture&, Rectangle, Vector2, Flip) const
{
}

void Renderer::AddSprite(Sprite2D* sprite)
{
}

void Renderer::RemoveSprite(Sprite2D* sprite)
{
}
