#pragma once
#include "Component.h"
#include "CommonLib.h"

class Rectangle;
class Actor;
class Gravity2D : public Component
{
private:
	Vector2 mVelocity;
	float maxSpeed	  { 500 };

	//Gravity YAY
	bool  mUseGravity	    { true };
	float mGravityStrength	{ 1.0f };
	float mGravity			{ 9.8f };
	Vector2 mGravityDir		{ 0, 1};

	Vector2 mLastPosition;
	Vector2 mCurrentDistance;

public:
	Vector2 getVelocity() { return mVelocity; }
	void setVelocity(Vector2 _v) { mVelocity = _v; }

	bool isTouchingFloor;

private:
public:
	Gravity2D(Actor* _pOwner, uint8_t _updateOrder);

	void Update(float _deltaTime) override;
	
	void Collided(Direction _direction, Vector2 _overlap);
};