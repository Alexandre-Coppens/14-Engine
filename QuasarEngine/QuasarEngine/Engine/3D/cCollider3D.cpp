#include "cCollider3D.h"

#include "Engine/Utilitaries/CommonLib.h"
#include "Engine/Actor.h"

#include "Engine/3D/cBoxCollider.h"
#include "Engine/3D/cSphereCollider.h"
#include "Engine/3D/cPhysicBody.h"
#include "Engine/Utilitaries/Log.h"
#include "Engine/Utilitaries/Managers/CollisionManager.h"

Collider3D::Collider3D(Actor* _pOwner):
    Component(_pOwner)
{
    mColliderType = NONE;
    CollisionManager::AddCollider(this);
}

Collider3D::~Collider3D()
{
}

void Collider3D::OnActorStart()
{
    mPhysicBased = pOwner->GetComponent<PhysicBody>() != nullptr;
}
void Collider3D::Update(float _deltaTime)
{
}

void Collider3D::CheckCollisions()
{
    //TODO: Tell the other collider to update its CollisionState
    mHasFrameCollision = false;
    if (mCollisionState == STOPPED_COLLIDING) mCollisionState = NOT_COLLIDING;
    if (mColliderType == NONE) return;
    if (!mPhysicBased) return;
    mCollisionList.clear();
    
    for (Collider3D* collider : CollisionManager::collidersList)
    {
        if (collider == this) continue;
        if (collider->getColliderType() == NONE) continue;
        
        CollisionData data = CollisionManager::GetIsColliding(this, collider);
        if (data.isColliding)
        {
            mCollisionList.push_back(data);
            //Log::Info(pOwner->getName() + " is Colliding with " + collider->getOwner()->getName());
            CollisionManager::ResolveCollisions(mCollisionList);
            mHasFrameCollision = true;
        }
    }
    if (mHasFrameCollision)
    {
        if (mCollisionState == COLLIDING) return;
        if (mCollisionState == NOT_COLLIDING) mCollisionState = START_COLLISION;
        else mCollisionState = COLLIDING;
    }
    else
    {
        if (mCollisionState == NOT_COLLIDING) return;
        mCollisionState = STOPPED_COLLIDING;
    }
}

void Collider3D::Destroy()
{
    CollisionManager::RemoveCollider(this);
    Component::Destroy();
}
