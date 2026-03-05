#pragma once

#include "Engine/Component.h"
#include "Engine/Utilitaries/CommonLib.h"

class Collider3D;
class PhysicBody : public Component
{
private:
    Vector3 mVelocity;
    
    bool mGravityEnabled      {true};
    float mMass               {0.1f};
    float mGravityForce       {9.8f};
    Vector3 mGravityDirection {Vector3UnitZ() * -1.0f};

public:
    float getMass() const {return mMass;}
    Vector3 getVelocity() const {return mVelocity;}

    void setVelocity(const Vector3 _velocity) {mVelocity = _velocity;}
    void setGravityEnabled(const bool _enable) {mGravityEnabled = _enable;}

    void addVelocity(const Vector3 _v) {mVelocity += _v;}
    void addVelocityX(const float _f) {mVelocity.x += _f;}
    void addVelocityY(const float _f) {mVelocity.y += _f;}
    void addVelocityZ(const float _f) {mVelocity.z += _f;}

private:
public:
    PhysicBody(Actor* _pOwner);
    ~PhysicBody() override;
    
    void Update(float _deltaTime) override;
    void ResolveCollision(Collider3D* _pOwnerCollision, Vector3 _nearestPoint);
    void ResolveVelocity(PhysicBody* _otherPhysic, Vector3 _nearestPoint, float _friction);
};