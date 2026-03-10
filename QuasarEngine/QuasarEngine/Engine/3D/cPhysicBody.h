#pragma once

#include "cCollider3D.h"
#include "Engine/Component.h"
#include "Engine/Utilitaries/CommonLib.h"

enum ColliderType;
class Collider3D;
class PhysicBody : public Component
{
private:
    ColliderType mColliderType;
    Collider3D* mpCollider;
    
    Vector3 mVelocity           {Vector3Zero()};
    Vector3 mAngularVelocity    {Vector3Zero()};
    Vector3 mTorque             {Vector3Zero()};
    Vector3 mInertia            {Vector3Zero()};
    
    //gravity
    bool mGravityEnabled      {true};
    float mMass               {0.1f};
    float mGravityForce       {9.8f};
    Vector3 mGravityDirection {Vector3NegUnitZ()};

public:
    float getMass()              const {return mMass;}
    Vector3 getVelocity()        const {return mVelocity;}
    Vector3 getAngularVelocity() const {return mAngularVelocity;}
    Collider3D* getReferencedCollider() const {return mpCollider;}
    
    void setMass(const float _f) {mMass = _f; RecalculateInertia();}
    void setVelocity(const Vector3 _velocity) {mVelocity = _velocity;}
    void setGravityEnabled(const bool _enable) {mGravityEnabled = _enable;}

    void addVelocity(const Vector3 _v) {mVelocity += _v;}
    void addVelocityX(const float _f)  {mVelocity.x += _f;}
    void addVelocityY(const float _f)  {mVelocity.y += _f;}
    void addVelocityZ(const float _f)  {mVelocity.z += _f;}
    
    void addTorque(const Vector3 _v)   {mTorque += _v;}

private:
    void RecalculateInertia();
    
public:
    PhysicBody(Actor* _pOwner, ColliderType _colliderType);
    ~PhysicBody() override;
    
    void OnStart() override;
    void Update(float _deltaTime) override;
    void ResolveCollision(Collider3D* _pOwnerCollision, CollisionData _collisionData);
    void ResolveVelocity(PhysicBody* _otherPhysic, CollisionData _collisionData, float _friction);
};