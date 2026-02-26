#include "cPhysic.h"
#include "Actor.h"

Physic::Physic(Actor* _pOwner):
    Component(_pOwner)
{
}

Physic::~Physic()
{
}

void Physic::Update(float _deltaTime)
{
    mVelocity += mGravityDirection * mGravityForce * mMass * _deltaTime;
    pOwner->getTransform3D()->addLocation(mVelocity * _deltaTime);
}