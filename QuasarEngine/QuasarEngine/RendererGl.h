#pragma once
#include "IRenderer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"

#include "CommonLib.h"

class Model;

class RendererGl : public IRenderer
{
private:
	Window* pWindow;
	VertexArray* pSpriteVao;
	ShaderProgram* pSpriteShaderProgram;
	SDL_GLContext mContext;
	std::vector<Sprite2D*> mSpriteList;
	std::vector<Model*> mModelList;
	Matrix4Row mView = Matrix4Row::Mat4RowIdentity();
	Matrix4Row mSpriteViewProj = Matrix4Row::Mat4RowIdentity();

public:
	void setShaderProgram(ShaderProgram* _pShaderProgram) { pSpriteShaderProgram = _pShaderProgram; }

public:
	RendererGl();
	virtual ~RendererGl();
	RendererGl(const RendererGl&) = delete;
	RendererGl& operator=(const RendererGl&) = delete;

	RendererType getType() override { return RendererType::OPENGL; }

	bool Initialize(Window& _rWindow) override;
	void BeginDraw() override;
	void Draw() override;
	void EndDraw() override;

	void DrawModels();
	void DrawSprites();
	void DrawSprite(Actor& _pActor, Texture* _pTex, Rectangle _SourceRect, Vector2 _v2Origin, Flip _Flip) const;

	void AddSprite(Sprite2D* _pSprite);
	void RemoveSprite(Sprite2D* _pSprite);

	void AddModel(Model* _pModel);
	void RemoveModel(Model* _pModel);

	void Close() override;
};
