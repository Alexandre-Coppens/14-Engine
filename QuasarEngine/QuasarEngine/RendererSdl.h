#pragma once
#include "IRenderer.h"

#include <vector>

class Actor;
class Texture;
class Sprite2D;
struct Rectangle;
class RendererSdl : public IRenderer
{
private:
	SDL_Renderer* pSDLRenderer;
	std::vector<Sprite2D*> mSpriteList = {};
public:
	SDL_Renderer* getSdlRenderer() const { return pSDLRenderer; }

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
	void DrawSprites();
	void DrawSprite(Actor& _pActor, const Texture* _pTex, const Rectangle& _sourceRect, Vector2 _origin, Flip _flip) const ;

	void AddSprite(Sprite2D* _pSprite);
	void RemoveSprite(const Sprite2D* _pSprite);

	void DrawDebugBox(const Rectangle& _rect, Vector2 _origin) const;
};