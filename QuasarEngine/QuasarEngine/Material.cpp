#include "Material.h"

#include "Actor.h"
#include "Scene.h"

Material::Material(Actor* _pOwner, Texture* _pTexture, uint8_t _drawOrder) :
	Component(_pOwner), mTexture(_pTexture), mDrawOrder(_drawOrder), mTextureWidth(mTexture->GetWidth()), mTextureHeight(_pTexture->GetHeight()), mXFlipped{ false }
{
	mName = "Material";
	pOwner->getScene()->getRendererGl()->AddSprite(this);
}

Material::~Material()
{
	pOwner->getScene()->getRendererGl()->RemoveSprite(this);
}

void Material::OnEnd()
{
	pOwner->getScene()->getRendererGl()->RemoveSprite(this);
}

void Material::SetTexture(Texture* _pTexture)
{
	mTexture = _pTexture;
	mTexture->UpdateInfo(mTextureWidth, mTextureHeight);
}

void Material::Draw(RendererGl& _pRenderer, DebugMode _debug)
{
	Vector2 origin{ 0.5f, 0.5f };
	_pRenderer.DrawSprite(*pOwner, mTexture, Rectangle(), origin, mXFlipped ? Flip::Horizontal : Flip::None);

	if (_debug == DebugMode::DRAWCOLLISIONS)
	{
		Rectangle rect = Rectangle(pOwner->getTransform2D()->getLocation(), pOwner->getTransform2D()->getSize());
		//_pRenderer.DrawDebugBox(rect, origin);
	}
}
