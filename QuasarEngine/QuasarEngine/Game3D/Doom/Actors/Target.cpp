#include "Target.h"

#include "Engine/3D/cBoxCollider.h"
#include "Engine/Utilitaries/Assets.h"

#include "Engine/3D/Mesh.h"
#include "Engine/Utilitaries/Time.h"

Target::Target() :
    DoomBaseActor()
{
    mName = "Door";
    Initialize();
}

Target::~Target()
{
}

void Target::Initialize()
{
    mModel = dynamic_cast<Model*>(AddComponent(new Model(this, "Transparent")));
    mCollider = dynamic_cast<BoxCollider*>(AddComponent(new BoxCollider(this)));
    DoomBaseActor::Initialize();
}

void Target::Start()
{
    mModel->setMesh(Assets::GetMesh(OBJ_cube));
    mModel->AddTexture(Assets::GetTexture(PNG_DemonFacing));

    mLife = mMaxLife;

    mTransform3D->addLocationZ(0.5f);
    mTransform3D->setScale(Vector3(0.05f, 0.5f, 0.5f));
    
    DoomBaseActor::Start();
}

void Target::Update(const float _deltaTime)
{
    if (mLife == 0)
    {
        mResurecting -= _deltaTime;
        GetDown();
        if (mResurecting <= 0)
        {
            mLife = mMaxLife;
        }
    }
    else GetUp();
    DoomBaseActor::Update(_deltaTime);
}

void Target::Destroy()
{
    DoomBaseActor::Destroy();
}

void Target::Interact()
{
}

void Target::Shoot()
{
    if (mLife == 0) return;
    mLife -= 1;
    if (mLife == 0)
    {
        mResurecting = mResurectTime;
    }
}

void Target::GetDown()
{
    if (mTransform3D->getRotation().y < 89.0f)
    {
        mTransform3D->addRotationY(90.0f * Time::deltaTime);
    }
}

void Target::GetUp()
{
    if (mTransform3D->getRotation().y > 1.0f)
    {
        mTransform3D->addRotationY(-30.0f * Time::deltaTime);
    }
}