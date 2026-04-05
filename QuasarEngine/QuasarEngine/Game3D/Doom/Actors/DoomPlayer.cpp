#include "DoomPlayer.h"

#include "Engine/Scene.h"
#include "Engine/.Prefabs/Object.h"
#include "Engine/Utilitaries/Assets.h"

#include "Engine/3D/Camera.h"
#include "Engine/3D/cBoxCollider.h"
#include "Engine/3D/cPhysicBody.h"
#include "Engine/Utilitaries/Log.h"
#include "Engine/Utilitaries/Managers/CollisionManager.h"
#include "Engine/Utilitaries/Managers/Inputs.h"

DoomPlayer::DoomPlayer() :
    Actor()
{
    mName = "Player";
}

DoomPlayer::~DoomPlayer()
{
}

void DoomPlayer::Start()
{
    mPhysicBody = dynamic_cast<PhysicBody*>(AddComponent(new PhysicBody(this, BOX)));
    mCollider = mPhysicBody->getReferencedCollider();
    mCamera = dynamic_cast<Camera*>(AddComponent(new Camera(this)));

    dynamic_cast<BoxCollider*>(mCollider)->setSize(Vector3One() * 0.1f);
    dynamic_cast<BoxCollider*>(mCollider)->setActive(false);
    mPhysicBody->setGravityEnabled(false);
    
    Actor::Start();
}

void DoomPlayer::Update(const float _deltaTime)
{
    if (Inputs::GetKey(SDLK_z))
    {
        // Vector3 forward = mCamera->getLocalTransform()->Forward();
        // forward.z = 0.0f;
        // forward = Normalize(forward);
        // mTransform3D->addLocation(forward * 1 * _deltaTime);
        mTransform3D->addLocation(mCamera->getLocalTransform()->Forward() * 1 * _deltaTime);
    }

    if (Inputs::GetKey(SDLK_s))
    {
        // Vector3 backward = mCamera->getLocalTransform()->Forward() * -1;
        // backward.z = 0.0f;
        // backward = Normalize(backward);
        // mTransform3D->addLocation(backward * 1 * _deltaTime);
        mTransform3D->addLocation(mCamera->getLocalTransform()->Forward() * -1 * _deltaTime);
    }

    if (Inputs::GetKey(SDLK_q))
    {
        // Vector3 left = mCamera->getLocalTransform()->Right() * -1;
        // mTransform3D->addLocation(left * 1 * _deltaTime);
        mTransform3D->addLocation(mCamera->getLocalTransform()->Right() * -1 * _deltaTime);
    }

    if (Inputs::GetKey(SDLK_d))
    {
        // Vector3 right = mCamera->getLocalTransform()->Right();
        // mTransform3D->addLocation(right * 1 * _deltaTime);
        mTransform3D->addLocation(mCamera->getLocalTransform()->Right() * 1 * _deltaTime);
    }
    
    /*if (Inputs::GetKeyDown(SDLK_r))
    {
        getScene()->getGame()->SetScene<Scene_Test>();
    }*/

    if (Inputs::GetKeyDown(SDLK_SPACE))
    {
        RaycastResult raycast = CollisionManager::Raycast(mCamera->getLocalTransform()->getWorldLocation(), mCamera->getLocalTransform()->Forward(), 99999.0f);
        Log::Info("Raycast result:" + std::to_string(raycast.hasHit));
        if (raycast.hasHit)
        {
            Log::Info("Hit Actor:" + raycast.actor->getName());
            Actor* cube = getScene()->AddActor(new Object("Cube", OBJ_Ball, PNG_Block, "BasicModel"));
            getScene()->InitNewActors();
            cube->getTransform3D()->setScale(0.2f);
            cube->getTransform3D()->setLocation(raycast.collisionPoint);
        }
    }
    
    //Rotation is stocked in a vector before being transformed to quat via ZYX order
    const float pitch = Inputs::GetMouseDeltaY() * 10.0f * _deltaTime;
    const float yaw = Inputs::GetMouseDeltaX() * 10.0f * _deltaTime;
    
    mCamera->getLocalTransform()->addRotationZ(yaw);
    mCamera->getLocalTransform()->addRotationY(pitch);
    mCamera->getLocalTransform()->clampRotationY(-89.0f, 89.0f);
    
    Actor::Update(_deltaTime);
}

void DoomPlayer::Destroy()
{
    Actor::Destroy();
}
