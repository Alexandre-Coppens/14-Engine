#include "Sprite2D.h"

#include <glew.h>

#include "Engine/Actor.h"
#include "Engine/Utilitaries/Rectangle.h"
#include "Engine/Scene.h"
#include "Engine/Utilitaries/Assets.h"
#include "Engine/Utilitaries/Time.h"

Sprite2D::Sprite2D(Actor* _pOwner, Texture* _pTexture, const uint8_t _drawOrder):
	Component(_pOwner), mTexture(_pTexture), mDrawOrder(_drawOrder), mTextureWidth(mTexture->GetWidth()), mTextureHeight(_pTexture->GetHeight()), mXFlipped{false}
{
	mTransform = Transform2D();
	pOwner->getScene()->getRendererSdl()->AddSprite(this);
}

Sprite2D::Sprite2D(Actor* _pOwner, Texture* _pTexture, std::string _shaderProgram, uint8_t _drawOrder):
	Component(_pOwner), mTexture(_pTexture), mDrawOrder(_drawOrder), mShader(_shaderProgram)
{
	mTransform = Transform2D();
	SetTexture(_pTexture);
	mTransform.setSize(Vector2{ mTextureWidth ,mTextureHeight});
	pOwner->getScene()->getRendererGl()->AddSprite(this, mDrawOrder);
}

Sprite2D::~Sprite2D() = default;

void Sprite2D::Destroy()
{
	if (mShader == "") pOwner->getScene()->getRendererSdl()->RemoveSprite(this);
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

void Sprite2D::DrawGL()
{
	if (!mIsActive) return;
	
	Assets::GetShaderProgram(mShader)->Use();
	Assets::GetShaderProgram(mShader)->SetMatrix4Row("uWorldTransform", mTransform.getViewportTransform());
	Assets::GetShaderProgram(mShader)->SetMatrix4Row("uViewProj", Mat4RowCreateSimpleViewProj(Window::GetSize().x, Window::GetSize().y));
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	
	float time = Time::currentFrameTime;
	Assets::GetShaderProgram(mShader)->SetFloat("uTime", time);
	
	mTexture->SetActive();
	TEXTURE NOT WORKING WELL
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
