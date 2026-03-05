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

//TODO: Change NearestPoint name because it does not represent the variable well anymore
void PhysicBody::ResolveCollision(Collider3D* _pOwnerCollision, Vector3 _nearestPoint)
{
    Vector3 collisionNormal = Normalize(pOwner->getTransform3D()->getLocation() - _nearestPoint);
    switch (_pOwnerCollision->getColliderType())
    {
    case BOX:
        {
            //please check here when head less full, need to make a AABB resolution system
            Vector3 position = dynamic_cast<BoxCollider*>(_pOwnerCollision)->getCenter();
            pOwner->getTransform3D()->addLocation(position - _nearestPoint);
        }
        break;
        
    case SPHERE:
        {
            //Check if Normalize len == 0
            if (collisionNormal == Vector3Zero())
            {
                collisionNormal = Normalize(_nearestPoint - pOwner->getTransform3D()->getLocation() - (mVelocity * Time::deltaTime));
            }
        
            float radius = dynamic_cast<SphereCollider*>(_pOwnerCollision)->getRadius();
            pOwner->getTransform3D()->setLocation(_nearestPoint + (collisionNormal * radius));
        }
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
        //From: https://stackoverflow.com/questions/17593700/collision-equation-for-two-3d-objects
        
        float mass1 = mMass;
        float mass2 = _otherPhysic->getMass();
        
        Vector3 oldVel1 = mVelocity;
        Vector3 oldVel2 = _otherPhysic->getVelocity();
        
        Vector3 newVel1 = oldVel1;
        Vector3 newVel2 = oldVel2;
        
        float e = _friction * 0.5f;
        
        newVel1 = ((mass1 - e*mass2) * oldVel1) / (mass1 + mass2);
        newVel2 = (2 * mass1 * oldVel1) / (mass1 + mass2);
        
        mVelocity = newVel1;
        _otherPhysic->setVelocity(newVel2);
        
        //mVelocity = Subtract(mVelocity, collisionNormal * ( (2 - _friction) * Dot(mVelocity, collisionNormal)));
        //_otherPhysic->setVelocity(Subtract(_otherPhysic->getVelocity(), collisionNormal * ( (2 - _friction) * Dot(_otherPhysic->getVelocity(), collisionNormal))));
    }
}

