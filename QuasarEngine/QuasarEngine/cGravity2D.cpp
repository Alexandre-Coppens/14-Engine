#include "cGravity2D.h"
#include "Log.h"

Gravity2D::Gravity2D(Actor* _pOwner, uint8_t _updateOrder):
	Component(_pOwner, _updateOrder), mVelocity(Vector2Zero())
{
}

void Gravity2D::Update()
{
	//if(mVelocity.y < 0)
}

void Gravity2D::Collided(Actor* _pOtherActor)
{
	//Vector2 
	Log::Info("No Collision implemented");
}
