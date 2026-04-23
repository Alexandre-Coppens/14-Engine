#include "Sprite2D.h"

#include <glew.h>

#include "Engine/Actor.h"
#include "Engine/Utilitaries/Rectangle.h"
#include "Engine/Scene.h"
#include "Engine/Render/Shaders/ShaderProgram.h"
#include "Engine/Utilitaries/Assets.h"

Sprite2D::Sprite2D(RendererType _rendererType, Actor* _pOwner, Texture* _pTexture, const uint8_t _drawOrder):
	Component(_pOwner),renderType(_rendererType), mTexture(_pTexture), mDrawOrder(_drawOrder), mTextureWidth(mTexture->GetWidth()), mTextureHeight(_pTexture->GetHeight()), mXFlipped{false}
{
	switch (_rendererType)
	{
		case RendererType::OPENGL:
			mTransform = Transform2D();
			SetTexture(_pTexture);
			mTransform.setSize(Vector2{ mTextureWidth ,mTextureHeight});
			pOwner->getScene()->getRendererGl()->AddSprite(this, mDrawOrder);
			break;

	case RendererType::SDL:
		mTransform = Transform2D();
		pOwner->getScene()->getRendererSdl()->AddSprite(this);
	}
}

Sprite2D::~Sprite2D() = default;

void Sprite2D::Destroy()
{
	if (renderType == RendererType::SDL) pOwner->getScene()->getRendererSdl()->RemoveSprite(this);
	else pOwner->getScene()->getRendererGl()->RemoveSprite(this, mDrawOrder);
	Component::Destroy();
}

void Sprite2D::SetTexture(Texture* _pTexture)
{
	mTexture = _pTexture;
	mTexture->UpdateInfo(mTextureWidth, mTextureHeight);
}

void Sprite2D::Draw(const RendererSdl& _pRenderer, DebugMode _debug)
{
	const Vector2 origin{ 0.5f, 0.5f };
	_pRenderer.DrawSprite(*pOwner, mTexture, Rectangle(), origin, mXFlipped ? Flip::Horizontal : Flip::None);
	
	if (_debug == DebugMode::DRAW_COLLISIONS)
	{
		Rectangle rect = Rectangle(pOwner->getTransform2D()->getLocation(), pOwner->getTransform2D()->getSize());
		//_pRenderer.DrawDebugBox(rect, origin);
	}
}

void Sprite2D::DrawGL(ShaderProgram* shader, int vertCount) {
	if (!mIsActive) return;
	
	shader->SetVector2f("uLocation", mTransform.getLocation());

	glActiveTexture(GL_TEXTURE0);
	mTexture->SetActive();
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
}
