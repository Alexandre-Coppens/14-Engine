#include "Preset_Actor.h"

#include "Engine/Utilitaries/Assets.h"

#include "Engine/3D/Mesh.h"

Preset_Actor::Preset_Actor() :
    Actor()
{
    mName = "Template";
    Initialize();
}

Preset_Actor::~Preset_Actor()
{
}

void Preset_Actor::Initialize()
{
    mModel = dynamic_cast<Model*>(AddComponent(new Model(this, PROG_BasicModel)));
    Actor::Initialize();
}

void Preset_Actor::Start()
{
    mModel->setMesh(Assets::GetMesh(OBJ_cube));
    mModel->getMaterial()->SetTexture("uTexture", Assets::GetTexture(PNG_NullTexture));
    Actor::Start();
}

void Preset_Actor::Update(const float _deltaTime)
{
    Actor::Update(_deltaTime);
}

void Preset_Actor::Destroy()
{
    Actor::Destroy();
}
