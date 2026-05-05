#pragma once
#include "Engine/Actor.h"
#include "Engine/3D/cModel.h"
#include "Engine/3D/cPhysicBody.h"

struct RaycastResult;
class Camera;
class DebugLine : public Actor
{
private:
    Model* mModel            {nullptr};

public:
    Model* getModel() const {return mModel;}

private:
    void ComputeLine(RaycastResult _result);
    
public:
    DebugLine(RaycastResult _result);
    ~DebugLine() override;

    void Initialize()               override;
    void Start()					override;
    void Update(float _deltaTime)	override;
    void Destroy()					override;
};
