#include "cSprite2D.h"

#include "Actor.h"
#include "Scene.h"

Sprite2D::Sprite2D(Actor* _pOwner, Texture& _pTexture, uint8_t _drawOrder):
	Component(_pOwner), mTexture(_pTexture), mDrawOrder(_drawOrder), mTextureWidth(mTexture.GetWidth()), mTextureHeight(_pTexture.GetHeight()), mXFlipped{false}
{
	pOwner->getScene()->getRendererSdl()->AddSprite(this);
}

Sprite2D::~Sprite2D()
{
	pOwner->getScene()->getRendererSdl()->RemoveSprite(this);
}

void Sprite2D::OnEnd()
{
	pOwner->getScene()->getRendererSdl()->RemoveSprite(this);
}

void Sprite2D::SetTexture(const Texture& _pTexture)
{
	mTexture = _pTexture;
	mTexture.UpdateInfo(mTextureWidth, mTextureHeight);
}

void Sprite2D::Draw(RendererSdl& _pRenderer, DebugMode _debug)
{
	Vector2 origin{ 0.5f, 0.5f };
	_pRenderer.DrawSprite(*pOwner, mTexture, Rectangle(), origin, mXFlipped ? Flip::Horizontal : Flip::None);
	
	if (_debug == DebugMode::DRAWCOLLISIONS)
	{
		Rectangle rect = Rectangle(pOwner->getTransform()->getLocation(), pOwner->getTransform()->getSize());
		//_pRenderer.DrawDebugBox(rect, origin);
	}
}
