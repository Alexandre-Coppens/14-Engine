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
void Collider3D::OnActorStart()
{
    mPhysicBased = pOwner->GetComponent<PhysicBody>() != nullptr;
}

void Collider3D::Update(const float _deltaTime)
{
    //TODO: Tell the other collider to update its CollisionState
    mHasFrameCollision = false;
    if (mCollisionState == STOPPED_COLLIDING) mCollisionState = NOT_COLLIDING;
    if (mColliderType == NONE) return;
    if (!mPhysicBased) return;
    for (Collider3D* collider : ColliderList)
    {
        if (collider == this) continue;
        if (collider->getColliderType() == NONE) continue;
        
        if (AreCollidersColliding(collider))
        {
            mHasFrameCollision = true;
            
            //Resolve Collisions entering each others
            PhysicBody* colliderPhysic = getOwner()->GetComponent<PhysicBody>();
            if (colliderPhysic == nullptr) continue;
            colliderPhysic->ResolveCollision(this, mNearestPoint);
            
            //Resolve Velocities
            PhysicBody* otherPhysic = collider->getOwner()->GetComponent<PhysicBody>();
            colliderPhysic->ResolveVelocity(otherPhysic, mNearestPoint, mFriction + collider->getFriction());
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
    
    if (not(boxA->getCenter().x - (boxA->getSize().x * 0.5f) <= boxB->getCenter().x + (boxB->getSize().x * 0.5f) &&
          boxA->getCenter().x + (boxA->getSize().x * 0.5f) >= boxB->getCenter().x - (boxB->getSize().x * 0.5f) &&
          boxA->getCenter().y - (boxA->getSize().y * 0.5f) <= boxB->getCenter().y + (boxB->getSize().y * 0.5f) &&
          boxA->getCenter().y + (boxA->getSize().y * 0.5f) >= boxB->getCenter().y - (boxB->getSize().y * 0.5f) &&
          boxA->getCenter().z - (boxA->getSize().z * 0.5f) <= boxB->getCenter().z + (boxB->getSize().z * 0.5f) &&
          boxA->getCenter().z + (boxA->getSize().z * 0.5f) >= boxB->getCenter().z - (boxB->getSize().z * 0.5f) )) 
        return false;
    
    //This is only for the nearest point
    Vector3 distance = boxB->getCenter() - boxA->getCenter();
    Vector3 absDistance;
    absDistance.x = Abs(distance.x);
    absDistance.y = Abs(distance.y);
    absDistance.z = Abs(distance.z);
    
    const Vector3 overlapp = (boxB->getSize() * 0.5f + boxA->getSize() * 0.5f) - absDistance;
    
    if      ( Abs(overlapp.x) <= Abs(overlapp.y) && Abs(overlapp.x) <= Abs(overlapp.z)) mNearestPoint = Vector3UnitX() * overlapp.x * (distance.x > 0 ? 1 : -1);
    else if ( Abs(overlapp.y) <= Abs(overlapp.x) && Abs(overlapp.y) <= Abs(overlapp.z)) mNearestPoint = Vector3UnitY() * overlapp.y * (distance.y > 0 ? 1 : -1);
    else mNearestPoint = Vector3UnitZ() * overlapp.z * (distance.z > 0 ? 1 : -1);
    
    mNearestPoint = boxA->getCenter() + mNearestPoint;
    
    return true;
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

