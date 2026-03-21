#pragma once

#include <vector>

#include "Engine/Component.h"
#include "Engine/Utilitaries/CommonLib.h"
#include "Engine/Utilitaries/MathLib.h"

class PhysicBody;
class BoxCollider;
enum ColliderType
{ 
    NONE,
    BOX,
    SPHERE
};

enum CollisionState
{
    NOT_COLLIDING,
    START_COLLISION,
    COLLIDING,
    STOPPED_COLLIDING
};

struct CollisionData
{
    PhysicBody* bodyA;
    PhysicBody* bodyB;

    float friction;
    
    float penetration;
    Vector3 normal;
    Vector3 collisionPoint;
};

class Collider3D : public Component
{
private:
    bool mHasFrameCollision;
    std::vector<CollisionData> mCollisionList;

protected:
    bool mPhysicBased                  {false};
    ColliderType mColliderType;
    CollisionState mCollisionState;
    float mFriction {0.5f};
    
    static std::vector<Collider3D*> ColliderList;
    
public:
    float getFriction()                 const {return mFriction;}
    ColliderType getColliderType()      const { return mColliderType; }
    CollisionState getCollisionState()  const { return mCollisionState; }
    
    //Friction clamped between 0 & 1
    void setFriction(float _f)  {mFriction = Clamp(_f, 0.0f, 1.0f);}

private:
    bool AreCollidersColliding(Collider3D* _pOther);
    void ResolveCollisions();
    
    bool BoxToBox(Collider3D* _pBoxA, Collider3D* _pBoxB);
    bool BoxToSphere(Collider3D* _pBox, Collider3D* _pSphere);
    bool SphereToSphere(Collider3D* _pSphereA, Collider3D* _pSphereB);
    
    float GetSeparatingPlane(const Vector3 _diffPos, const Vector3 _plane, BoxCollider* _boxA, BoxCollider* _boxB);
    
public:
    Collider3D(Actor* _pOwner);
    ~Collider3D() override;
    
    void OnActorStart() override;
    void Update(const float _deltaTime) override;
    void Destroy() override;
    
    virtual Vector3 getCenter() = 0;
    void virtual DrawDebug() = 0;
};
