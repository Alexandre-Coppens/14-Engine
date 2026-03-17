#include "cAnimation2D.h"

#include "Engine/Utilitaries/Time.h"

AnimatedSprite2D::AnimatedSprite2D(Actor* _pOwner, const std::vector<Texture*>& _pTextures, const int _drawOrder):
	Sprite2D(_pOwner, _pTextures[0], static_cast<Uint8>(_drawOrder)), mCurrentFrame(0.0f), mAnimFPS(24.0f)
{
	setAnimationTextures(_pTextures);
}

AnimatedSprite2D::~AnimatedSprite2D()
{
	for (Texture* a : mAnimationTextures)
	{
		delete a;
		a = nullptr;
	}
	mAnimationTextures.clear();
}

void AnimatedSprite2D::Update(const float _deltaTime)
{
	Sprite2D::Update(_deltaTime);
	if (mAnimationTextures.empty()) return;
	mCurrentFrame += mAnimFPS * Time::deltaTime;
	while (mCurrentFrame >= mAnimationTextures.size())
	{
		mCurrentFrame -= mAnimationTextures.size();
	}
	SetTexture(mAnimationTextures[static_cast<int>(mCurrentFrame)]);
}
