#include "Door.h"

#include <chrono>
#include <thread>

#include "Engine/3D/cBoxCollider.h"
#include "Engine/Utilitaries/Assets.h"

#include "Engine/3D/Mesh.h"
#include "Engine/Utilitaries/Time.h"

Door::Door() :
    DoomBaseActor()
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
    DoomBaseActor::Initialize();
}

void Door::Start()
{
    mModel->setMesh(Assets::GetMesh(OBJ_cube));
    mModel->AddTexture(Assets::GetTexture(PNG_Door));
    mTransform3D->addLocationZ(0.5f);
    mTransform3D->setScale(Vector3(0.05f, 1.0f, 1.0f));
    startHeight = mTransform3D->getLocation().z;
    DoomBaseActor::Start();
}

void Door::Update(const float _deltaTime)
{
    if (needOpening)
    {
        Open();
    }
    if (needWaiting)
    {
        Wait();
    }
    if (needClosing)
    {
        Close();
    }
    DoomBaseActor::Update(_deltaTime);
}

void Door::Destroy()
{
    DoomBaseActor::Destroy();
}

void Door::Interact()
{
    if (isLocked) return;
    if (needClosing) return;
    needOpening = true;
}

void Door::Open()
{
    if (currentHeight < openHeight)
    {
        currentHeight += Time::deltaTime * speed;
        mTransform3D->addLocationZ(Time::deltaTime * speed);
    }
    else
    {
        needOpening = false;
        mTransform3D->setLocationZ(startHeight + openHeight);
        currentTimer = openTimer;
        needWaiting = true;
    }
}

void Door::Wait()
{
    if (currentTimer > 0.0f)
    {
        currentTimer -= Time::deltaTime;
    }
    else
    {
        needWaiting = false;
        needClosing = true;
    }
}

void Door::Close()
{
    if (currentHeight > 0.0f)
    {
        currentHeight -= Time::deltaTime * speed;
        mTransform3D->addLocationZ(-Time::deltaTime * speed);
    }
    else
    {
        needClosing = false;
        mTransform3D->setLocationZ(startHeight);
    }
}
