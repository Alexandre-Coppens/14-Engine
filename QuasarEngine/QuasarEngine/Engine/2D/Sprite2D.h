#ifndef SPRITE_2D_H
#define SPRITE_2D_H

#include "Engine/Component.h"
#include "Engine/Texture.h"
#include "Engine/2D/Transform2D.h"
#include "Engine/Utilitaries/CommonLib.h"
#include "Engine/Render/RendererSdl.h"

class Material;
class ShaderProgram;
class Sprite2D : public Component
{
protected:
	RendererType renderType;
	
	Texture* mTexture;
	uint8_t  mDrawOrder;
	float mTextureWidth;
	float mTextureHeight;
	bool mXFlipped;

	//GL
	Transform2D mTransform;

public:
	uint16_t getDrawOrder()		  const	{ return mDrawOrder; }
	float getTextureWidth()	  const	{ return mTextureWidth; }
	float getTextureHeight()	  const	{ return mTextureHeight; }
	Vector2  getTextureSize()	  const	{ return Vector2{ static_cast<float>(mTextureWidth), static_cast<float>(mTextureHeight) }; }

	void setXFlip(const bool _b) { mXFlipped = _b; }

	Transform2D* getTransform()	        { return &mTransform; }

private:
public:
	Sprite2D(RendererType _rendererType, Actor* _pOwner, Texture* _pTexture, uint8_t _drawOrder);
	~Sprite2D() override;
	Sprite2D() = delete;
	Sprite2D(const Sprite2D&) = delete;
	Sprite2D& operator= (const Sprite2D&) = delete;

	void Update(float _deltaTime)	override {};
	void Destroy() override;

	virtual void SetTexture(Texture* _pTexture);
	virtual void Draw(const RendererSdl& _pRenderer, DebugMode _debug);
	void DrawGL(ShaderProgram* shader);
};

#endif // !1