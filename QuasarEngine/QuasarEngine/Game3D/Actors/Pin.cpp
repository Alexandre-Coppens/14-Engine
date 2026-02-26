#include "Pin.h"

#include "Engine/Utilitaries/Assets.h"

#include "Engine/cModel.h"
#include "Engine/Mesh.h"

Pin::Pin() :
    Actor()
{
    mName = "Pin";
}

Pin::~Pin()
{
}

void Pin::Start()
{
    mModel = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
    mModel->setMesh(Assets::GetMesh("Pin"));
    mModel->getMesh()->AddTexture(Assets::GetTexture("Pin"));
    Actor::Start();
}

void Pin::Update(const float _deltaTime)
{
    Actor::Update(_deltaTime);
}

void Pin::Destroy()
{
    Actor::Destroy();
}
