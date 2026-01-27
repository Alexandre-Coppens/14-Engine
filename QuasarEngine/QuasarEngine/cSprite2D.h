#ifndef SPRITE2D_H
#define SPRITE2D_H

#include "Component.h"
#include "CommonLib.h"
#include "Texture.h"
#include "Renderer.h"

class Sprite2D : public Component
{
protected:
	Texture	 mTexture;
	uint8_t  mDrawOrder;
	uint16_t mTextureWidth;
	uint16_t mTextureHeight;
	Vector2  mSize;
	float	 mRotation;

public:
	uint16_t getDrawOrder()		  const	{ return mDrawOrder; }
	uint16_t getTextureWidth()	  const	{ return mTextureWidth; }
	uint16_t getTextureHeight()	  const	{ return mTextureHeight; }
	Vector2  getTextureSize()	  const	{ return Vector2{ (float)mTextureWidth, (float)mTextureHeight }; }
	float	 getTextureRotation() const	{ return mRotation; }
	
	void   setSize(Vector2 _v2)  { mSize = _v2;}
	float  setRotation(float _f) { mRotation = _f;}

private:
public:
	Sprite2D(Actor* _pOwner, Texture& _pTexture, Vector2 _size, uint8_t _drawOrder);
	virtual ~Sprite2D();
	Sprite2D() = delete;
	Sprite2D(const Sprite2D&) = delete;
	Sprite2D& operator= (const Sprite2D&) = delete;

	void Update()	override {};

	virtual void SetTexture(const Texture& _pTexture);
	virtual void Draw(Renderer& _pRenderer);
};

#endif // !1