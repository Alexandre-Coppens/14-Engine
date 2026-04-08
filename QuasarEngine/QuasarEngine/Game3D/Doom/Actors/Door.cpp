#include "Door.h"

#include "Engine/3D/cBoxCollider.h"
#include "Engine/Utilitaries/Assets.h"

#include "Engine/3D/Mesh.h"

Door::Door() :
    Actor()
{
    mName = "Door";
    Initialize();
}

Door::~Door()
{
}

void Door::Initialize()
{
    mModel = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
    mCollider = dynamic_cast<BoxCollider*>(AddComponent(new BoxCollider(this)));
    Actor::Initialize();
}

void Door::Start()
{
    mModel->setMesh(Assets::GetMesh(OBJ_cube));
    mModel->getMesh()->AddTexture(Assets::GetTexture(PNG_Block));
    
    Actor::Start();
}

void Door::Update(const float _deltaTime)
{
    if (needOpening)
    {
        if (currentHeight < openHeight)
        {
            currentHeight += _deltaTime * speed;
            mTransform3D->addLocationZ(_deltaTime * speed);
        }
        else
        {
            needOpening = false;
        }
    }
    Actor::Update(_deltaTime);
}

void Door::Destroy()
{
    Actor::Destroy();
}

void Door::Interact()
{
    if (needClosing) return;
    needOpening = true;
}

void Door::Open()
{
    
}

void Door::Close()
{
}
