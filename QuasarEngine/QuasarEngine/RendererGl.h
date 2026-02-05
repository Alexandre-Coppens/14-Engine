#pragma once
#include "IRenderer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"

class Sprite2D;

class RendererGl : public IRenderer
{
private:
	Window* pWindow;
	VertexArray* pVao;
	ShaderProgram* pShaderProgram;
	SDL_GLContext mContext;
	std::vector<Sprite2D*> mSprites;

public:
	void setShaderProgram(ShaderProgram* _pShaderProgram) { pShaderProgram = _pShaderProgram; }

public:
	RendererGl();
	virtual ~RendererGl();
	RendererGl(const RendererGl&) = delete;
	RendererGl& operator=(const RendererGl&) = delete;

	RendererType getType() override { return RendererType::OPENGL; }

	bool Initialize(Window& _rWindow) override;
	void BeginDraw() override;
	void Draw() override;
	void DrawSprites() override;
	void EndDraw() override;

	void DrawSprite(Actor& _pActor, const Texture& _pTex, Rectangle _sourceRect, Vector2 _origin, Flip _flip = Flip::None) const override;
	void AddSprite(Sprite2D* _pSprite);
	void RemoveSprite(Sprite2D* _pSprite);
	void Close() override;
};
