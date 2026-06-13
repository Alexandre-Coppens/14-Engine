#include "Planet.h"

#include "Engine/Utilitaries/Assets.h"

#include "Engine/3D/Mesh.h"

Planet::Planet() :
    Actor()
{
    mName = "Template";
    Initialize();
}

Planet::~Planet()
{
}

void Planet::Initialize()
{
    mModel = dynamic_cast<Model*>(AddComponent(new Model(this, PROG_BasicModel)));
    Actor::Initialize();
}

void Planet::Start()
{
    mModel->setMesh(Assets::GetMesh(OBJ_cube));
    mModel->getMaterial()->SetTexture("uTexture", Assets::GetTexture(PNG_NullTexture));
    Actor::Start();
}

void Planet::Update(const float _deltaTime)
{
    Actor::Update(_deltaTime);
}

void Planet::Destroy()
{
    Actor::Destroy();
}
