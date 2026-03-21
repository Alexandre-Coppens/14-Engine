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
    mCollisionList.clear();
    for (Collider3D* collider : ColliderList)
    {
        if (collider == this) continue;
        if (collider->getColliderType() == NONE) continue;
        
        if (AreCollidersColliding(collider))
        {
            Log::Info(pOwner->getName() + " is Colliding with " + collider->getOwner()->getName());
            mHasFrameCollision = true;
        }
    }
    if (mHasFrameCollision)
    {
        ResolveCollisions();
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
    Component::Destroy();
    std::vector<Collider3D*>::iterator it;
    it = std::find(ColliderList.begin(), ColliderList.end(), this);
    ColliderList.erase(it);
}

void Collider3D::ResolveCollisions()
{
    for (CollisionData data : mCollisionList)
    {
        bool elasticCollision = data.bodyA != nullptr && data.bodyB != nullptr;
        if (elasticCollision) data.penetration *= 0.5f;

        if (data.bodyA != nullptr)
        {
            data.bodyA->ResolveCollision(data);
            data.bodyA->ResolveVelocity(data);
        }
        data.normal *= -1;
        if (data.bodyB != nullptr)
        {
            data.bodyB->ResolveCollision(data);
            data.bodyB->ResolveVelocity(data);
        }
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
    
    for (int i = 0; i < axisList.size(); i++)
    {
        if (Length(axisList[i]) < 0.001f)
        {
            axisList.erase(axisList.begin() + i);
            i--;
        }
    }
    
    int smallestAxeIndex = 0;
    float smallestPenetration = INFINITY_POS;
    float separatingPlane = 0;
    
    for (int i = 0; i < axisList.size(); i++)
    {
        separatingPlane = GetSeparatingPlane(diffDist, axisList[i], boxA, boxB);
        if (separatingPlane > 0) return false;
        if (Abs(separatingPlane) < smallestPenetration)
        {
            smallestPenetration = Abs(separatingPlane);
            smallestAxeIndex = i;
        }
    }

    CollisionData collisionData;
    collisionData.penetration = smallestPenetration;
    collisionData.normal = Normalize(axisList[smallestAxeIndex]);
    if (Dot(collisionData.normal, diffDist) > 0) collisionData.normal *= -1;
    
    std::vector<Vector3> vertexList = boxA->getWorldVertices();
    Vector3 contactPointA = vertexList[0];
    float maxProjection = Dot(vertexList[0], collisionData.normal);
    float projection = 0;
    
    for (int i = 0; i < vertexList.size(); i++)
    {
        projection = Dot(vertexList[i], collisionData.normal);
        if (projection > maxProjection)
        {
            maxProjection = projection;
            contactPointA = vertexList[i];
        }
    }

    vertexList = boxB->getWorldVertices();
    Vector3 contactPointB = vertexList[0];
    maxProjection = Dot(vertexList[0], collisionData.normal * -1);
    
    for (int i = 0; i < vertexList.size(); i++)
    {
        projection = Dot(vertexList[i], collisionData.normal * -1);
        if (projection > maxProjection)
        {
            maxProjection = projection;
            contactPointB = vertexList[i];
        }
    }
    
    collisionData.collisionPoint = (contactPointA + contactPointB) * 0.5f;
    collisionData.friction = boxA->getFriction() + boxB->getFriction();

    collisionData.bodyA = boxA->getOwner()->GetComponent<PhysicBody>();
    collisionData.bodyB = boxB->getOwner()->GetComponent<PhysicBody>();
    
    mCollisionList.push_back(collisionData);
    
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
    
    Vector3 closestPoint = boxLocation;
    Vector3 delta = sphereLocation - boxLocation;
        
    float projection = Dot(delta, forwardBoxAxis);
    float clamp = Clamp(projection, -box->getSize().x * 0.5f, box->getSize().x * 0.5f);
    closestPoint += forwardBoxAxis * clamp;
    
    projection = Dot(delta, rightBoxAxis);
    clamp = Clamp(projection, -box->getSize().y * 0.5f, box->getSize().y * 0.5f);
    closestPoint += rightBoxAxis * clamp;
    
    projection = Dot(delta, upBoxAxis);
    clamp = Clamp(projection, -box->getSize().z * 0.5f, box->getSize().z * 0.5f);
    closestPoint += upBoxAxis * clamp;
    
    Vector3 difference = sphereLocation - closestPoint;
    
    if (!(Pow(Length(difference)) < Pow(sphereRadius))) return false;

    //Add Collision to List
    CollisionData collisionData;
    
    collisionData.penetration = sphereRadius - Length(difference) /*Distance(sphereLocation, closestPoint)*/;
    if (collisionData.penetration < 0.001f) return false;
    
    collisionData.normal = Normalize(difference);
    if (collisionData.normal == Vector3(0.0f, 0.0f, 0.0f)) collisionData.normal = Normalize(sphereLocation - boxLocation);
    
    collisionData.collisionPoint = closestPoint;
    collisionData.friction = box->getFriction() + sphere->getFriction();

    collisionData.bodyA = sphere->getOwner()->GetComponent<PhysicBody>();
    collisionData.bodyB = box->getOwner()->GetComponent<PhysicBody>();
    
    mCollisionList.push_back(collisionData);
    
    return true;
}

//Check if sphere Distance < sphere combined Radius
bool Collider3D::SphereToSphere(Collider3D* _pSphereA, Collider3D* _pSphereB)
{
    Vector4 s1 = dynamic_cast<SphereCollider*>(_pSphereA)->GetSphere();
    Vector4 s2 = dynamic_cast<SphereCollider*>(_pSphereB)->GetSphere();

    Vector4 dist = s1 - s2;

    if (!(Pow(dist.x) + Pow(dist.y) + Pow(dist.z) < Pow(s1.w + s2.w))) return false;

    //Add Collision to List
    CollisionData collisionData;
    
    collisionData.penetration = s1.w + s2.w - Distance(Vector3{s1.x, s1.y, s1.z}, Vector3{s2.x, s2.y, s2.z});
    collisionData.normal = Normalize(Vector3{dist.x, dist.y, dist.z});
    collisionData.collisionPoint = collisionData.normal * s1.w + (collisionData.penetration);
    
    collisionData.friction = _pSphereA->getFriction() + _pSphereB->getFriction();

    collisionData.bodyA = _pSphereA->getOwner()->GetComponent<PhysicBody>();
    collisionData.bodyB = _pSphereB->getOwner()->GetComponent<PhysicBody>();
    
    mCollisionList.push_back(collisionData);
    
    return true;
}

float Collider3D::GetSeparatingPlane(const Vector3 _diffPos, const Vector3 _plane, BoxCollider* _boxA, BoxCollider* _boxB)
{
    return (Abs(Dot(_diffPos, _plane)) -
        (Abs(Dot((_boxA->getForward() *  _boxA->getScale().x * 0.5f), _plane)) +
         Abs(Dot((_boxA->getRight()   *  _boxA->getScale().y * 0.5f), _plane)) +
         Abs(Dot((_boxA->getUp()      *  _boxA->getScale().z * 0.5f), _plane)) +
         Abs(Dot((_boxB->getForward() *  _boxB->getScale().x * 0.5f), _plane)) +
         Abs(Dot((_boxB->getRight()   *  _boxB->getScale().y * 0.5f), _plane)) +
         Abs(Dot((_boxB->getUp()      *  _boxB->getScale().z * 0.5f), _plane))));
}

