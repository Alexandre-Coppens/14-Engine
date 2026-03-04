#include "cPhysicBody.h"

#include "Engine/3D/cSphereCollider.h"
#include "Engine/3D/cBoxCollider.h"
#include "Engine/3D/cCollider3D.h"
#include "Engine/Actor.h"

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
        pOwner->getTransform3D()->addLocation(collisionNormal * (radius + 0.01f));
        break;
    }
}

