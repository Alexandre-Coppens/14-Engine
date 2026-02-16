#ifndef MATERIAL_H
#define MATERIAL_H

#include "Component.h"
#include "CommonLib.h"
#include "Texture.h"
#include "RendererGl.h"

class Material : public Component
{
protected:
	Texture	 mTexture;
	uint8_t  mDrawOrder;
	uint16_t mTextureWidth;
	uint16_t mTextureHeight;
	bool mXFlipped;

public:
	uint16_t getDrawOrder()		  const { return mDrawOrder; }
	uint16_t getTextureWidth()	  const { return mTextureWidth; }
	uint16_t getTextureHeight()	  const { return mTextureHeight; }
	Vector2  getTextureSize()	  const { return Vector2{ (float)mTextureWidth, (float)mTextureHeight }; }

	void setXFlip(bool _b) { mXFlipped = _b; }

private:
public:
	Material(Actor* _pOwner, Texture& _pTexture, uint8_t _drawOrder);
	virtual ~Material();
	Material() = delete;
	Material(const Material&) = delete;
	Material& operator= (const Material&) = delete;

	void Update(float _deltaTime)	override {};
	void OnEnd() override;

	virtual void SetTexture(const Texture& _pTexture);
	virtual void Draw(RendererSdl& _pRenderer, DebugMode _debug);
};

#endif // !1