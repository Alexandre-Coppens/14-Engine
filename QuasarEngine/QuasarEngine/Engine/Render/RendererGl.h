#pragma once
#include <map>
#include <vector>

#include "Engine/Utilitaries/CommonLib.h"
#include "Engine/Render/IRenderer.h"

class VertexArray;
class CameraManager;
class Model;
class ShaderProgram;
class RendererGl : public IRenderer
{
private:
	Window* pWindow;
	SDL_GLContext mContext;
	
	VertexArray* pSpriteVao;
	ShaderProgram* pSpriteShaderProgram;
	std::vector<Sprite2D*> mSpriteList;
	
	std::map<ShaderProgram*, std::vector<Model*>> mModelDrawOrder;
	
	Matrix4Row mView = Matrix4Row::Mat4RowIdentity();
	Matrix4Row mProj = Matrix4Row::Mat4RowIdentity();
	Matrix4Row mSpriteViewProj = Matrix4Row::Mat4RowIdentity();

public:
	void setViewMatrix(const Matrix4Row _view) {mView = _view;}
	void setShaderProgram(ShaderProgram* _pShaderProgram) { pSpriteShaderProgram = _pShaderProgram; }

	Matrix4Row getViewMatrix() { return mView * mProj; }
	SDL_GLContext getContext() { return mContext; }
	
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

	void DrawModels() const;
	void DrawSprites();
	
	void AddSprite(Sprite2D* _pSprite);
	void RemoveSprite(Sprite2D* _pSprite);

	void AddModel(Model* _pModel, ShaderProgram* _pShaderProgram);
	void RemoveModel(Model* _pModel, ShaderProgram* _pShaderProgram);

	void AddShaderProgram(ShaderProgram* _pShaderProgram);
	void RemoveShaderProgram(ShaderProgram* _pShaderProgram);

	void Close() override;
};
