#include "cCollider3D.h"

#include "Engine/Utilitaries/CommonLib.h"
#include "Engine/Actor.h"

#include "Engine/3D/cBoxCollider.h"
#include "Engine/3D/cSphereCollider.h"
#include "Engine/3D/cPhysicBody.h"
#include "Engine/Utilitaries/Log.h"

std::vector<Collider3D*> Collider3D::ColliderList;

Collider3D::Collider3D(Actor* _pOwner):
    Component(_pOwner)
{
    mColliderType = NONE;
    ColliderList.push_back(this);
}

Collider3D::~Collider3D()
{
    std::vector<Collider3D*>::iterator it;
    it = std::find(ColliderList.begin(), ColliderList.end(), this);
    ColliderList.erase(it);
}

void Collider3D::Update(const float _deltaTime)
{
    mHasFrameCollision = false;
    if (mCollisionState == STOPPED_COLLIDING) mCollisionState = NOT_COLLIDING;
    if (mColliderType == NONE) return;
    for (Collider3D* collider : ColliderList)
    {
        if (collider == this) continue;
        if (collider->getColliderType() == NONE) continue;
        
        if (AreCollidersColliding(collider))
        {
            Log::Info(pOwner->getName() + " Collision");
            mHasFrameCollision = true;
            PhysicBody* colliderPhysic = collider->getOwner()->GetComponent<PhysicBody>();
            colliderPhysic->ResolveCollision(this, mNearestPoint);
            if (colliderPhysic == nullptr) continue;
            //TODO: resolve velocity
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

//Return is the 2 colliders are colliding.
bool Collider3D::AreCollidersColliding(Collider3D* _pOther)
{
    if (mColliderType == BOX)
    {
        switch (_pOther->getColliderType())
        {
            case BOX:
                return BoxToBox(this, _pOther);
            case SPHERE:
                return BoxToSphere(this, _pOther);
        }
    }
    else if (mColliderType == SPHERE)
    {
        switch (_pOther->getColliderType())
        {
        case BOX:
            return BoxToSphere(_pOther, this);
        case SPHERE:
            return SphereToSphere(this, _pOther);
        }
    }
    return false;
}

bool Collider3D::BoxToBox(Collider3D* _pBoxA, Collider3D* _pBoxB)
{
    BoxCollider* boxA = dynamic_cast<BoxCollider*>(_pBoxA);
    BoxCollider* boxB = dynamic_cast<BoxCollider*>(_pBoxB);
    
    //This is only for the nearest point
    const float x = Max(boxB->getCenter().x - (boxB->getSize().x * 0.5f), Min(boxA->getCenter().x, boxB->getCenter().x + (boxB->getSize().x * 0.5f)));
    const float y = Max(boxB->getCenter().y - (boxB->getSize().y * 0.5f), Min(boxA->getCenter().y, boxB->getCenter().y + (boxB->getSize().y * 0.5f)));
    const float z = Max(boxB->getCenter().z - (boxB->getSize().z * 0.5f), Min(boxA->getCenter().z, boxB->getCenter().z + (boxB->getSize().z * 0.5f)));
    
    mNearestPoint = Vector3(x, y, z);
    return (
          boxA->getCenter().x - (boxA->getSize().x * 0.5f) <= boxB->getCenter().x + (boxB->getSize().x * 0.5f) &&
          boxA->getCenter().x + (boxA->getSize().x * 0.5f) >= boxB->getCenter().x - (boxB->getSize().x * 0.5f) &&
          boxA->getCenter().y - (boxA->getSize().y * 0.5f) <= boxB->getCenter().y + (boxB->getSize().y * 0.5f) &&
          boxA->getCenter().y + (boxA->getSize().y * 0.5f) >= boxB->getCenter().y - (boxB->getSize().y * 0.5f) &&
          boxA->getCenter().z - (boxA->getSize().z * 0.5f) <= boxB->getCenter().z + (boxB->getSize().z * 0.5f) &&
          boxA->getCenter().z + (boxA->getSize().z * 0.5f) >= boxB->getCenter().z - (boxB->getSize().z * 0.5f) 
        );
}

bool Collider3D::BoxToSphere(Collider3D* _pBox, Collider3D* _pSphere)
{
    BoxCollider* box = dynamic_cast<BoxCollider*>(_pBox);
    Vector4 sphere = dynamic_cast<SphereCollider*>(_pSphere)->GetSphere();
    
    // get box closest point to sphere center by clamping
    const float x = Max(box->getCenter().x - (box->getSize().x * 0.5f), Min(sphere.x, box->getCenter().x + (box->getSize().x * 0.5f)));
    const float y = Max(box->getCenter().y - (box->getSize().y * 0.5f), Min(sphere.y, box->getCenter().y + (box->getSize().y * 0.5f)));
    const float z = Max(box->getCenter().z - (box->getSize().z * 0.5f), Min(sphere.z, box->getCenter().z + (box->getSize().z * 0.5f)));
    
    const float distance =
        Pow(x - sphere.x)+
        Pow(y - sphere.y)+
        Pow(z - sphere.z);

    mNearestPoint = Vector3(x, y, z);
    return distance < Pow(sphere.w);
}

//Check if dist2(sphereA, sphereB) <= dist2(sphereA.rad, sphereB.rad)
bool Collider3D::SphereToSphere(Collider3D* _pSphereA, Collider3D* _pSphereB)
{
    Vector4 s1 = dynamic_cast<SphereCollider*>(_pSphereA)->GetSphere();
    Vector4 s2 = dynamic_cast<SphereCollider*>(_pSphereB)->GetSphere();

    s2.w *= -1;

    Vector4 dist = s1 - s2;

    dist.w *= -1;
    
    mNearestPoint = Vector3(s2.x, s2.y, s2.z);
    return Pow(dist.x) + Pow(dist.y) + Pow(dist.z) - Pow(s1.w + s2.w) <= 0;
}

