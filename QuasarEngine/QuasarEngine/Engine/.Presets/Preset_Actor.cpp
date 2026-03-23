#include "Preset_Actor.h"

#include "Engine/Utilitaries/Assets.h"

#include "Engine/3D/Mesh.h"

Preset_Actor::Preset_Actor() :
    Actor()
{
    mName = "Template";
}

Preset_Actor::~Preset_Actor()
{
}

void Preset_Actor::Start()
{
    mModel = dynamic_cast<Model*>(AddComponent(new Model(this, "Null")));
    
    mModel->setMesh(Assets::GetMesh(TODO));
    mModel->getMesh()->AddTexture(Assets::GetTexture("Null"));
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
