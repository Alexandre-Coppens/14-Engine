#pragma once
#include "Engine/Actor.h"
#include "Engine/3D/cModel.h"

class Collider3D;
class PhysicBody;
class Camera;
class DoomPlayer : public Actor
{
private:
    Model* mModel            {nullptr};
    Collider3D* mCollider    {nullptr};
    PhysicBody* mPhysicBody  {nullptr};
    Camera* mCamera          {nullptr};

public:
    Model* getModel() const {return mModel;}

private:
public:
    DoomPlayer();
    ~DoomPlayer() override;
    
    void Initialize()               override;
    void Start()					override;
    void Update(float _deltaTime)	override;
    void Destroy()					override;
};
