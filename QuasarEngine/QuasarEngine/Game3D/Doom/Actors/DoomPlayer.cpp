#include "DoomPlayer.h"

#include "Engine/Utilitaries/Assets.h"

#include "Engine/3D/Camera.h"
#include "Engine/3D/cBoxCollider.h"
#include "Engine/3D/cPhysicBody.h"
#include "Engine/Utilitaries/Inputs.h"

DoomPlayer::DoomPlayer() :
    Actor()
{
    mName = "Template";
}

DoomPlayer::~DoomPlayer()
{
}

void DoomPlayer::Start()
{
    mCollider = dynamic_cast<BoxCollider*>(AddComponent(new BoxCollider(this)));
    mPhysicBody = dynamic_cast<PhysicBody*>(AddComponent(new PhysicBody(this, BOX)));
    mCamera = dynamic_cast<Camera*>(AddComponent(new Camera(this)));

    mPhysicBody->setGravityEnabled(true);
    
    Actor::Start();
}

void DoomPlayer::Update(const float _deltaTime)
{
    Actor::Update(_deltaTime);
    
    if (Inputs::GetKey(SDLK_z))
    {
        mTransform3D.addLocation(mCamera->getLocalTransform()->Forward() * 1 * _deltaTime);
    }

    if (Inputs::GetKey(SDLK_s))
    {
        mTransform3D.addLocation(mCamera->getLocalTransform()->Forward() * -1 * _deltaTime);
    }

    if (Inputs::GetKey(SDLK_q))
    {
        mTransform3D.addLocation(mCamera->getLocalTransform()->Right() * -1 * _deltaTime);
    }

    if (Inputs::GetKey(SDLK_d))
    {
        mTransform3D.addLocation(mCamera->getLocalTransform()->Right() * 1 * _deltaTime);
    }
    
    /*if (Inputs::GetKeyDown(SDLK_r))
    {
        getScene()->getGame()->SetScene<Scene_Test>();
    }*/
    
    //Rotation is stocked in a vector before being transformed to quat via ZYX order
    const float pitch = Inputs::GetMouseDeltaY() * 10.0f * _deltaTime;
    const float yaw = Inputs::GetMouseDeltaX() * 10.0f * _deltaTime;
    
    mCamera->getLocalTransform()->addRotationZ(yaw);
    mCamera->getLocalTransform()->addRotationY(pitch);
    mCamera->getLocalTransform()->clampRotationY(-89.0f, 89.0f);
    mCamera->getLocalTransform()->computeRotation();
}

void DoomPlayer::Destroy()
{
    Actor::Destroy();
}
