#pragma once

#include <vector>

#include "Engine/Component.h"
#include "Engine/Utilitaries/CommonLib.h"

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

class Collider3D : public Component
{
private:
    bool mHasFrameCollision;
    //Used for PhysicBody repositions & velocity calculs
    Vector3 mNearestPoint;

protected:
    ColliderType mColliderType;
    CollisionState mCollisionState;
    
    static std::vector<Collider3D*> ColliderList;
    
public:
    ColliderType getColliderType() { return mColliderType; }
    CollisionState getCollisionState() { return mCollisionState; }
    
public:
    Collider3D(Actor* _pOwner);
    ~Collider3D() override;
    
    void Update(const float _deltaTime) override;
    void virtual DrawDebug() = 0;

    bool AreCollidersColliding(Collider3D* _pOther);
    
    bool BoxToBox(Collider3D* _pBoxA, Collider3D* _pBoxB);
    bool BoxToSphere(Collider3D* _pBox, Collider3D* _pSphere);
    bool SphereToSphere(Collider3D* _pSphereA, Collider3D* _pSphereB);
};
