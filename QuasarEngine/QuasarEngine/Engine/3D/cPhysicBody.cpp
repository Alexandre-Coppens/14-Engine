#include "cPhysicBody.h"

#include "Engine/3D/cSphereCollider.h"
#include "Engine/3D/cBoxCollider.h"
#include "Engine/3D/cCollider3D.h"

#include "Engine/Actor.h"

#include "Engine/Utilitaries/Log.h"
#include "Engine/Utilitaries/Time.h"

PhysicBody::PhysicBody(Actor* _pOwner):
    Component(_pOwner)
{
}

PhysicBody::~PhysicBody()
{
}

void PhysicBody::Update(float _deltaTime)
{
    if (mGravityEnabled) mVelocity += mGravityDirection * mGravityForce * mMass * _deltaTime;
    pOwner->getTransform3D()->addLocation(mVelocity * _deltaTime);
}

//TODO: Resolve Velocity repartition
void PhysicBody::ResolveCollision(Collider3D* _pOwnerCollision, Vector3 _nearestPoint)
{
    Vector3 collisionNormal = Normalize(_nearestPoint - pOwner->getTransform3D()->getLocation());
    //Check if Normalize len == 0
    if (collisionNormal == Vector3Zero())
    {
        collisionNormal = Normalize(_nearestPoint - pOwner->getTransform3D()->getLocation() - (mVelocity * Time::deltaTime));
    }
    
    switch (_pOwnerCollision->getColliderType())
    {
    case BOX:
        {
            BoxCollider* collider = dynamic_cast<BoxCollider*>(_pOwnerCollision);
            collisionNormal = Vector3{
                collisionNormal.x * collider->getSize().x * 0.501f,
                collisionNormal.y * collider->getSize().y * 0.501f,
                collisionNormal.z * collider->getSize().z * 0.501f };
            pOwner->getTransform3D()->addLocation(collisionNormal);
        }
        break;
        
    case SPHERE:
        float radius = dynamic_cast<SphereCollider*>(_pOwnerCollision)->getRadius();
        pOwner->getTransform3D()->setLocation(_nearestPoint + (collisionNormal * (radius) * -1.0f));
        Log::Info("Start");
        Log::Info("NearestPoint: " + ToString(_nearestPoint));
        Log::Info("CollisionNormal: " + ToString(collisionNormal));
        Log::Info("Radius: " + std::to_string(radius));
        Log::Info("End");
        break;
    }
}

void PhysicBody::ResolveVelocity(PhysicBody* _otherPhysic, Vector3 _nearestPoint, float _friction)
{
    Vector3 collisionNormal = Normalize(_nearestPoint - pOwner->getTransform3D()->getLocation());
    if (_otherPhysic == nullptr)
    {
        //Friction is already between 0 & 2 since it's the combination of the 2 frictions
        mVelocity = Subtract(mVelocity, collisionNormal * ( (2 - _friction) * Dot(mVelocity, collisionNormal)));
    }
    else
    {
        //TODO: Add mass to this
        mVelocity = Subtract(mVelocity, collisionNormal * ( (2 - _friction) * Dot(mVelocity, collisionNormal)));
    }
}

