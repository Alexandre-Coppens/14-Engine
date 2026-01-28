#pragma once
#include "Component.h"
#include "CommonLib.h"

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

public:


private:
public:
	Gravity2D(Actor* _pOwner, uint8_t _updateOrder);

	void Update() override;
	
	void Collided(Actor* _pOtherActor);
};