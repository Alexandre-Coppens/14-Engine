#pragma once
#include <vector>

#include "IRenderer.h"
#include "CommonLib.h"
#include "VertexArray.h"

class CameraManager;
class Model;
class ShaderProgram;
class RendererGl : public IRenderer
{
private:
	Window* pWindow;
	CameraManager* pCameraManager;
	VertexArray* pSpriteVao;
	ShaderProgram* pSpriteShaderProgram;
	SDL_GLContext mContext;
	std::vector<Sprite2D*> mSpriteList;
	std::vector<Model*> mModelList;
	Matrix4Row mView = Matrix4Row::Mat4RowIdentity();
	Matrix4Row mProj = Matrix4Row::Mat4RowIdentity();
	Matrix4Row mSpriteViewProj = Matrix4Row::Mat4RowIdentity();

public:
	void setViewMatrix(const Matrix4Row _view) {mView = _view;}
	void setShaderProgram(ShaderProgram* _pShaderProgram) { pSpriteShaderProgram = _pShaderProgram; }

public:
	RendererGl();
	virtual ~RendererGl() override;
	RendererGl(const RendererGl&) = delete;
	RendererGl& operator=(const RendererGl&) = delete;

	RendererType getType() override { return RendererType::OPENGL; }

	bool Initialize(Window& _rWindow) override;
	void BeginDraw() override;
	void Draw() override;
	void EndDraw() override;

	void DrawModels();
	void DrawSprites();
	
	void AddSprite(Sprite2D* _pSprite);
	void RemoveSprite(Sprite2D* _pSprite);

	void AddModel(Model* _pModel);
	void RemoveModel(Model* _pModel);

	void Close() override;
};
