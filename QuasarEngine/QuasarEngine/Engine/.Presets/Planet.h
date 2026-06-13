#pragma once
#include "Engine/Actor.h"
#include "Engine/3D/cModel.h"
#include "Engine/3D/cPhysicBody.h"

class Camera;
class Planet : public Actor
{
private:
    Model* mModel            {nullptr};
    PhysicBody* mPhysicBody  {nullptr};

public:
    Model* getModel() const {return mModel;}

private:
public:
    Planet();
    ~Planet() override;

    void Initialize()               override;
    void Start()					override;
    void Update(float _deltaTime)	override;
    void Destroy()					override;
};
