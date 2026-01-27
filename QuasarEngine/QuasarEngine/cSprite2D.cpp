#include "cSprite2D.h"

#include "Actor.h"
#include "Scene.h"

Sprite2D::Sprite2D(Actor* _pOwner, Texture& _pTexture, Vector2 _v2Size, uint8_t _u8DrawOrder):
	Component(_pOwner), texture(_pTexture), u8DrawOrder(_u8DrawOrder), u16TextureWidth(texture.GetWidth()), Size(_v2Size), u16TextureHeight(texture.GetHeight())
{
	pOwner->GetScene()->GetRenderer()->AddSprite(this);
}

Sprite2D::~Sprite2D()
{
	pOwner->GetScene()->GetRenderer()->RemoveSprite(this);
}

void Sprite2D::SetTexture(const Texture& _pTexture)
{
	texture = _pTexture;
	texture.UpdateInfo(u16TextureWidth, u16TextureHeight);
}

void Sprite2D::Draw(Renderer& _pRenderer)
{
	Vector2 origin{ 0.5f, 0.5f };
	_pRenderer.DrawSprite(*pOwner, texture, Rectangle(),  Size, origin, Renderer::Flip::None);
}
