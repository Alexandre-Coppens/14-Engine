#include "cPhysicBody.h"

#include "Engine/3D/cSphereCollider.h"
#include "Engine/3D/cBoxCollider.h"
#include "Engine/3D/cCollider3D.h"

#include "Engine/Actor.h"

#include "Engine/Utilitaries/Log.h"
#include "Engine/Utilitaries/Time.h"
#include "Engine/Utilitaries/Managers/CollisionManager.h"

//PhysicBody have it's own collider to calculate Inertia for the angular velocity
PhysicBody::PhysicBody(Actor* _pOwner, ColliderType _colliderType) :
    Component(_pOwner), mColliderType(_colliderType)
{
    switch (mColliderType)
    {
    case ColliderType::SPHERE:
        mpCollider = dynamic_cast<Collider3D*>(pOwner->AddComponent(new SphereCollider(pOwner)));
        break;
        
    case ColliderType::BOX:
        mpCollider = dynamic_cast<Collider3D*>(pOwner->AddComponent(new BoxCollider(pOwner)));
        break;
    }
    mpCollider->setDebugColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
    RecalculateInertia();
}
PhysicBody::~PhysicBody()
{
    mpCollider = nullptr;
}

void PhysicBody::OnStart()
{
    Component::OnStart();
    RecalculateInertia();
}

void PhysicBody::Update(float _deltaTime)
{
    Vector3 force = Vector3Zero();
    if (mGravityEnabled) force += (mGravityDirection * mGravityForce) * mMass;
    mVelocity += (force / mMass) * _deltaTime * 0.1f;
    pOwner->getTransform3D()->addLocation(mVelocity * _deltaTime);
    
    /*Vector3 angularAcceleration = Vector3Zero();
    angularAcceleration = mTorque / mInertia;
    mAngularVelocity += angularAcceleration * _deltaTime;
    pOwner->getTransform3D()->addRotation((mAngularVelocity * 180.0f / PI) * _deltaTime);
    mTorque = 0;*/
}

//TODO: Change NearestPoint name because it does not represent the variable well anymore
void PhysicBody::ResolveCollision(const CollisionData _data)
{
    pOwner->getTransform3D()->addLocation(_data.normal * (_data.penetration + 0.0001f));
    pOwner->getTransform3D()->ComputeWorldTransform();
    //Log::Info(pOwner->getName() + "::" + ToString(_data.normal)+ " : " + std::to_string(_data.penetration));
}

void PhysicBody::ResolveVelocity(const CollisionData _data)
{
    bool hasExchange = _data.bodyA != nullptr && _data.bodyB != nullptr;
    PhysicBody* otherBody = nullptr;
    if (hasExchange) otherBody = (_data.bodyA == this ? _data.bodyB : _data.bodyA);

    Vector3 otherVelocity = Vector3Zero();
    float otherMass = 0.0f;
    if (hasExchange)
    {
        otherVelocity = otherBody->getVelocity();
        otherMass = otherBody->getMass();
    }
    
    float invMass1 = 1/mMass;
    float invMass2 = otherMass != 0.0f ? 1/otherMass : 0.0f;

    Vector3 n = Normalize(_data.normal);
    
    float e = 0.25f;
    Vector3 relative = mVelocity - otherVelocity;
    float j = -(1 + e) * Dot(relative, n) / Dot(_data.normal, _data.normal * (invMass1 + invMass2));
    
    mVelocity += (j * invMass1) * _data.normal;
    
    //Log::Info(pOwner->getName() + "::" + ToString(mVelocity));
}

void PhysicBody::Destroy()
{
    mpCollider = nullptr;
    Component::Destroy();
}

void PhysicBody::RecalculateInertia()
{
    switch (mColliderType)
    {
    case BOX:
        {
            Vector3 size = static_cast<BoxCollider*>(mpCollider)->getSize();
            mInertia.x = (1.0f/12.0f) * mMass * (Pow(size.z) + Pow(size.x));
            mInertia.y = (1.0f/12.0f) * mMass * (Pow(size.y) + Pow(size.x));
            mInertia.z = (1.0f/12.0f) * mMass * (Pow(size.y) + Pow(size.z));
        }
        break;
        
    case SPHERE:
        {
            float radius = static_cast<SphereCollider*>(mpCollider)->getRadius();
            mInertia = (2.0f/5.0f) * mMass * Pow(radius);
        }
        break;
    }
}