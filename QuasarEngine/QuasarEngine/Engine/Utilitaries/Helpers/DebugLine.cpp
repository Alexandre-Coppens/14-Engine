#include "DebugLine.h"

#include "Engine/Utilitaries/Assets.h"

#include "Engine/3D/Mesh.h"
#include "Engine/Utilitaries/Managers/CollisionManager.h"

DebugLine::DebugLine(RaycastResult _result) :
    Actor()
{
    mName = "DebugLine";
    Initialize();
    ComputeLine(_result);
}

DebugLine::~DebugLine()
{
}

void DebugLine::Initialize()
{
    mModel = dynamic_cast<Model*>(AddComponent(new Model(this, "Simple")));
    Actor::Initialize();
}

void DebugLine::Start()
{
    mModel->setMesh(Assets::GetMesh(OBJ_cube));
    Actor::Start();
}

void DebugLine::Update(const float _deltaTime)
{
    Actor::Update(_deltaTime);
}

void DebugLine::Destroy()
{
    Actor::Destroy();
}

void DebugLine::ComputeLine(RaycastResult _result)
{
    mTransform3D->setLocation((_result.rayStart + _result.collisionPoint) * 0.5f);
    mTransform3D->setScale(Vector3(_result.distance, 0.01f, 0.01f));

    Vector3 dir = _result.rayDirection;

    float yaw = ToDeg(atan2f(dir.y, dir.x));
    float pitch = ToDeg(atan2f(dir.z, sqrt(Pow(dir.x) + Pow(dir.y))));

    mTransform3D->setRotation(Vector3(0.0f, pitch, yaw + 180.0f));
}