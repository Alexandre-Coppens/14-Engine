#ifndef SPRITE2D_H
#define SPRITE2D_H

#include "Component.h"
#include "CommonLib.h"
#include "Texture.h"
#include "Renderer.h"

class Sprite2D : public Component
{
protected:
	Texture texture;
	uint8_t u8DrawOrder;
	uint16_t u16TextureWidth;
	uint16_t u16TextureHeight;
	Vector2 Size;

public:
	uint16_t GetDrawOrder()		const	{ return u8DrawOrder; }
	uint16_t GetTextureWidth()	const	{ return u16TextureWidth; }
	uint16_t GetTextureHeight()	const	{ return u16TextureHeight; }
	Vector2 GetTextureSize()	const	{ return Vector2{ (float)u16TextureWidth, (float)u16TextureHeight }; }
	Vector2 SetSize(Vector2 _v2) { Size = _v2;}

private:
public:
	Sprite2D(Actor* _pOwner, Texture& _pTexture, Vector2 _v2Size, uint8_t _u8DrawOrder);
	virtual ~Sprite2D();
	Sprite2D() = delete;
	Sprite2D(const Sprite2D&) = delete;
	Sprite2D& operator= (const Sprite2D&) = delete;

	void Update()	override {};

	virtual void SetTexture(const Texture& _pTexture);
	virtual void Draw(Renderer& _pRenderer);
};

#endif // !1