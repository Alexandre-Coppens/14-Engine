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
            colliderPhysic->ResolveCollision(this, mCollisionData);
            
            //Resolve Velocities
            PhysicBody* otherPhysic = collider->getOwner()->GetComponent<PhysicBody>();
            colliderPhysic->ResolveVelocity(otherPhysic, mCollisionData, mFriction + collider->getFriction());
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
    
    Vector3 diffDist = boxB->getCenter() - boxA->getCenter();
    
    std::vector<Vector3> axisList = {
        boxA->getForward(),
        boxA->getRight(),     
        boxA->getUp(),        
        boxB->getForward(),   
        boxB->getRight(),     
        boxB->getUp(),        
        Cross(boxA->getForward(), boxB->getForward()), 
        Cross(boxA->getForward(), boxB->getRight()),   
        Cross(boxA->getForward(), boxB->getUp()),      
        Cross(boxA->getRight(),   boxB->getForward()), 
        Cross(boxA->getRight(),   boxB->getRight()),   
        Cross(boxA->getRight(),   boxB->getUp()),      
        Cross(boxA->getUp(),      boxB->getForward()), 
        Cross(boxA->getUp(),      boxB->getRight()),   
        Cross(boxA->getUp(),      boxB->getUp())   
    };
    
    Uint8 smallestAxeIndex = 0;
    float smallestPenetration = INFINITY_POS;
    float separatingPlane = 0;
    
    for (int i = 0; i < axisList.size(); i++)
    {
        separatingPlane = GetSeparatingPlane(diffDist, axisList[i], boxA, boxB);
        if (separatingPlane < 0.0001f) return false;
        if (separatingPlane < smallestPenetration)
        {
            smallestPenetration = separatingPlane;
            smallestAxeIndex = i;
        }
    }
    
    mCollisionData.penetration = smallestPenetration;
    mCollisionData.normal = axisList[smallestAxeIndex];
   
    return true;
}

bool Collider3D::BoxToSphere(Collider3D* _pBox, Collider3D* _pSphere)
{
    BoxCollider* box = dynamic_cast<BoxCollider*>(_pBox);
    SphereCollider* sphere = dynamic_cast<SphereCollider*>(_pSphere);
    
    Vector3 sphereLocation = sphere->getCenter();
    float sphereRadius = sphere->getRadius();
    
    Vector3 boxLocation = box->getCenter();
    Vector3 forwardBoxAxis = box->getForward();
    Vector3 rightBoxAxis = box->getRight();
    Vector3 upBoxAxis = box->getUp();
    
    float projection = 0;
    float clamp = 0;
    Vector3 closestPoint = boxLocation;
    Vector3 delta = sphereLocation - boxLocation;
        
    projection = Dot(delta, forwardBoxAxis);
    clamp = Clamp(projection, -box->getSize().x * 0.5f, box->getSize().x * 0.5f);
    closestPoint += forwardBoxAxis * clamp;
    
    projection = Dot(delta, rightBoxAxis);
    clamp = Clamp(projection, -box->getSize().y * 0.5f, box->getSize().y * 0.5f);
    closestPoint += rightBoxAxis * clamp;
    
    projection = Dot(delta, upBoxAxis);
    clamp = Clamp(projection, -box->getSize().z * 0.5f, box->getSize().z * 0.5f);
    closestPoint += upBoxAxis * clamp;
        
    Vector3 difference = sphereLocation - closestPoint;
    
    if (!(Pow(Length(difference)) < Pow(sphereRadius))) return false;
    
    mCollisionData.penetration = sphereRadius - Distance(sphereLocation, closestPoint);
    if (mCollisionData.penetration < 0.0001f) return false;
    
    if (mCollisionData.penetration < 0.0001f) mCollisionData.normal = Normalize(delta);
    else mCollisionData.normal = Normalize(sphereLocation - closestPoint);
    mCollisionData.collisionPoint = closestPoint;
    
    return true;
}

//Check if sphere Distance < sphere combined Radius
bool Collider3D::SphereToSphere(Collider3D* _pSphereA, Collider3D* _pSphereB)
{
    Vector4 s1 = dynamic_cast<SphereCollider*>(_pSphereA)->GetSphere();
    Vector4 s2 = dynamic_cast<SphereCollider*>(_pSphereB)->GetSphere();

    Vector4 dist = s1 - s2;

    if (!(Pow(dist.x) + Pow(dist.y) + Pow(dist.z) < Pow(s1.w + s2.w))) return false;
    
    mCollisionData.penetration = s1.w + s2.w - Distance(Vector3{s1.x, s1.y, s1.z}, Vector3{s2.x, s2.y, s2.z});
    mCollisionData.normal = Normalize(Vector3{dist.x, dist.y, dist.z});
    mCollisionData.collisionPoint = mCollisionData.normal * s1.w + (mCollisionData.penetration);
    return true;
}

float Collider3D::GetSeparatingPlane(const Vector3 _diffPos, const Vector3 _plane, BoxCollider* _boxA, BoxCollider* _boxB)
{
    return (Abs(Dot(_diffPos, _plane)) -
        (Abs(Dot((_boxA->getForward() *  _boxA->getSize().x * 0.5f), _plane)) +
         Abs(Dot((_boxA->getRight()   *  _boxA->getSize().y * 0.5f), _plane)) +
         Abs(Dot((_boxA->getUp()      *  _boxA->getSize().z * 0.5f), _plane)) +
         Abs(Dot((_boxB->getForward() *  _boxB->getSize().x * 0.5f), _plane)) +
         Abs(Dot((_boxB->getRight()   *  _boxB->getSize().y * 0.5f), _plane)) +
         Abs(Dot((_boxB->getUp()      *  _boxB->getSize().z * 0.5f), _plane))));
}

