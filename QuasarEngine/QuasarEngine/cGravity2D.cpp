#include "cGravity2D.h"
#include "Log.h"
#include "Actor.h"

Gravity2D::Gravity2D(Actor* _pOwner, uint8_t _updateOrder):
	Component(_pOwner, _updateOrder), mVelocity(Vector2Zero()), mLastPosition(Vector2Zero())
{
}

void Gravity2D::Update(float _deltaTime)
{
	if(mUseGravity) mVelocity = mVelocity + (mGravityDir * mGravity * mGravityStrength );
	getOwner()->getTransform()->addLocation(mVelocity * _deltaTime);
	mCurrentDistance = mLastPosition - pOwner->getTransform()->getLocation();
	mLastPosition = pOwner->getTransform()->getLocation();
	isTouchingFloor = false;
	Log::Info(ToString(getVelocity()));
}

void Gravity2D::Collided(Direction _direction, Vector2 _overlap)
{
	switch (_direction)
	{
	case Direction::UP:
		mVelocity.y = 0;
		pOwner->getTransform()->addLocationY(_overlap.y);
		break;

	case Direction::DOWN:
		mVelocity.y = 0;
		isTouchingFloor = true;
		pOwner->getTransform()->addLocationY(_overlap.y);
		break;

	case Direction::LEFT:
		mVelocity.x = 0;
		pOwner->getTransform()->addLocationX(_overlap.x);
		break;

	case Direction::RIGHT:
		mVelocity.x = 0;
		pOwner->getTransform()->addLocationX(_overlap.x);
		break;

	case Direction::CENTER:
		if (mVelocity.x > mVelocity.y)
		{
			mVelocity.x = 0;
			pOwner->getTransform()->addLocationX(_overlap.x);
		}
		else
		{
			mVelocity.y = 0;
			pOwner->getTransform()->addLocationY(_overlap.y);
		}
		break;
	}
}

