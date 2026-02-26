#pragma once

#include "Engine/Component.h"
#include "Engine/Utilitaries/CommonLib.h"

class Physic : public Component
{
protected:
    Vector3 mVelocity;
    
    bool mGravityEnabled {false};
    float mMass {0.1f};
    float mGravityForce {9.8f};
    Vector3 mGravityDirection {Vector3UnitZ() * -1.0f};

public:
    Vector3 getVelocity() const {return mVelocity;}

    void setVelocity(const Vector3 _velocity) {mVelocity = _velocity;}

    void addVelocity(const Vector3 _v) {mVelocity += _v;}
    void addVelocityX(const float _f) {mVelocity.x += _f;}
    void addVelocityY(const float _f) {mVelocity.y += _f;}
    void addVelocityZ(const float _f) {mVelocity.z += _f;}

private:
public:
    Physic(Actor* _pOwner);
    ~Physic() override;
    
    void Update(float _deltaTime) override;
};