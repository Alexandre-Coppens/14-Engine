#include "cAnimation2D.h"

#include "Time.h"

AnimatedSprite2D::AnimatedSprite2D(Actor* _pOwner, const std::vector<Texture*>& _pTextures, int _drawOrder):
	Sprite2D(_pOwner, *_pTextures[0], _drawOrder), mCurrentFrame(0.0f), mAnimFPS(24.0f)
{
	setAnimationTextures(_pTextures);
}

AnimatedSprite2D::~AnimatedSprite2D()
{
}

void AnimatedSprite2D::Update()
{
	Sprite2D::Update();
	if (mAnimationTextures.size() == 0) return;
	mCurrentFrame += mAnimFPS * Time::deltaTime;
	while (mCurrentFrame >= mAnimationTextures.size())
	{
		mCurrentFrame -= mAnimationTextures.size();
	}
	SetTexture(*mAnimationTextures[static_cast<int>(mCurrentFrame)]);
}
