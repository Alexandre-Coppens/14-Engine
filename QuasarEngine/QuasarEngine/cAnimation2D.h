#pragma once
#include "cSprite2D.h"

#include <vector>

class AnimatedSprite2D : public Sprite2D
{
private:
	std::vector<Texture*> mAnimationTextures;
	float mCurrentFrame;
	float mAnimFPS;

public:
	float getFrameRate() const { return mAnimFPS; }

	void setFrameRate(float _fps) { mAnimFPS = _fps; }
	void setAnimationTextures(const std::vector<Texture*>& _pTextures) {
		mAnimationTextures = _pTextures;
		if (mAnimationTextures.size() > 0) SetTexture(*mAnimationTextures[0]);
	}

private:
public:
	AnimatedSprite2D(Actor* _pOwner, const std::vector<Texture*>& _pTextures, int _drawOrder = 100);
	virtual ~AnimatedSprite2D();
	AnimatedSprite2D() = delete;
	AnimatedSprite2D(const AnimatedSprite2D&) = delete;
	AnimatedSprite2D& operator= (const AnimatedSprite2D&) = delete;

	void Update(float _deltaTime) override;
};