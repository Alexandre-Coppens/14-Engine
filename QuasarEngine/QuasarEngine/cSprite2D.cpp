#include "cSprite2D.h"

#include "Actor.h"
#include "Scene.h"

Sprite2D::Sprite2D(Actor* _pOwner, Texture& _pTexture, uint8_t _drawOrder):
	Component(_pOwner), mTexture(_pTexture), mDrawOrder(_drawOrder), mTextureWidth(mTexture.GetWidth()), mTextureHeight(_pTexture.GetHeight()), mXFlipped{false}
{
	pOwner->getScene()->getRenderer()->AddSprite(this);
}

Sprite2D::~Sprite2D()
{
	pOwner->getScene()->getRenderer()->RemoveSprite(this);
}

void Sprite2D::SetTexture(const Texture& _pTexture)
{
	mTexture = _pTexture;
	mTexture.UpdateInfo(mTextureWidth, mTextureHeight);
}

void Sprite2D::Draw(RendererSdl& _pRenderer)
{
	Vector2 origin{ 0.5f, 0.5f };
	_pRenderer.DrawSprite(*pOwner, mTexture, Rectangle(), origin, mXFlipped ? RendererSdl::Flip::Horizontal : RendererSdl::Flip::None);
}
