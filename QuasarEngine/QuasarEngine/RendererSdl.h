#pragma once
#include <SDL_Image.h>
#include "IRenderer.h"

#include <vector>

class Sprite2D;
class Actor;
class Texture;
class RendererSdl : public IRenderer
{
private:
	SDL_Renderer* pSDLRenderer;
	std::vector<Sprite2D*> mSpriteList = {};
public:
	SDL_Renderer* getSdlRenderer() { return pSDLRenderer; }

private:
public:
	RendererSdl();
	RendererSdl(const RendererSdl&) = delete;
	RendererSdl& operator= (const RendererSdl&) = delete;

	RendererType getType() override { return RendererType::SDL; }

	bool Initialize(Window& _pWindow) override;
	void BeginDraw() override;
	void EndDraw() override;
	void Close() override;

	void Draw() override;
	void DrawSprites() override;
	void DrawSprite(Actor& _pActor, const Texture& _pTex, Rectangle _SourceRect, Vector2 _v2Origin, Flip _Flip) const override;

	void AddSprite(Sprite2D* _pSprite);
	void RemoveSprite(Sprite2D* _pSprite);

	void DrawDebugBox(Rectangle _rect, Vector2 _origin);
};