#include "cPhysicBody.h"

#include "Engine/3D/cSphereCollider.h"
#include "Engine/3D/cBoxCollider.h"
#include "Engine/3D/cCollider3D.h"

#include "Engine/Actor.h"

#include "Engine/Utilitaries/Log.h"
#include "Engine/Utilitaries/Time.h"

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
    mVelocity += force * _deltaTime * 0.01f;
    pOwner->getTransform3D()->addLocation(mVelocity * _deltaTime);
    
    Vector3 angularAcceleration = Vector3Zero();
    angularAcceleration = mTorque / mInertia;
    mAngularVelocity += angularAcceleration * _deltaTime;
    pOwner->getTransform3D()->addRotation((mAngularVelocity * 180.0f / PI) * _deltaTime);
    mTorque = 0;
}

//TODO: Change NearestPoint name because it does not represent the variable well anymore
void PhysicBody::ResolveCollision(Collider3D* _pOwnerCollision, Vector3 _nearestPoint)
{
    Vector3 collisionNormal = Normalize(pOwner->getTransform3D()->getLocation() - _nearestPoint);
    switch (_pOwnerCollision->getColliderType())
    {
    case BOX:
        {
            Vector3 position = dynamic_cast<BoxCollider*>(_pOwnerCollision)->getCenter();
            pOwner->getTransform3D()->addLocation(position - _nearestPoint);
        }
        break;
        
    case SPHERE:
        {
            //Check if Normalize len == 0
            if (collisionNormal == Vector3Zero())
            {
                collisionNormal = Normalize(pOwner->getTransform3D()->getLocation() - (mVelocity * Time::deltaTime) - _nearestPoint);
            }
        
            float radius = dynamic_cast<SphereCollider*>(_pOwnerCollision)->getRadius();
            pOwner->getTransform3D()->setLocation(_nearestPoint + (collisionNormal * radius));
        }
        break;
    }
}

void PhysicBody::ResolveVelocity(PhysicBody* _otherPhysic, Vector3 _nearestPoint, float _friction)
{
    Vector3 collisionNormal = Normalize(pOwner->getTransform3D()->getLocation() - _nearestPoint);
    Vector3 r = _nearestPoint - pOwner->getTransform3D()->getLocation();
    Vector3 force = Vector3Zero();
    if (_otherPhysic == nullptr)
    {
        //Friction is already between 0 & 2 since it's the combination of the 2 frictions
        mVelocity = Subtract(mVelocity, collisionNormal * ( (2 - _friction) * Dot(mVelocity, collisionNormal)));
        switch (mColliderType)
        {
        case BOX:
            force = mVelocity * -1;
            break;
            
        case SPHERE:
            float radius = static_cast<SphereCollider*>(mpCollider)->getRadius();
            mAngularVelocity = (1/radius) * Cross(collisionNormal, mVelocity);
            break;
        }

    }
    else
    {
        //From: https://stackoverflow.com/questions/17593700/collision-equation-for-two-3d-objects
        
        float mass1 = mMass;
        float mass2 = _otherPhysic->getMass();
        
        Vector3 oldVel1 = mVelocity;
        Vector3 oldVel2 = _otherPhysic->getVelocity();
        
        Vector3 newVel1 = oldVel1;
        Vector3 newVel2 = oldVel2;
        
        float e = _friction * 0.5f;
        
        newVel1 = ((mass1 - e*mass2) * oldVel1 + (1 + e) * mass2 * oldVel2) / (mass1 + mass2);
        newVel2 = ((mass2 - e*mass1) * oldVel2 + (1 + e) * mass1 * oldVel1) / (mass1 + mass2);
        
        mVelocity = newVel1;
        _otherPhysic->setVelocity(newVel2);
        
        force = newVel1 - oldVel1;
        _otherPhysic->addTorque(Cross(_nearestPoint - _otherPhysic->getReferencedCollider()->getCenter(), newVel2 - oldVel2));
    }
    mTorque += Cross(r, force);
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
            mInertia.x = (1.0f/12.0f) * mMass * (Pow(size.y) + Pow(size.z));
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