#include "Player3D.h"

#include "Engine/Game.h"
#include "Engine/Scene.h"
#include "Engine/Utilitaries/Assets.h"
#include "Engine/Utilitaries/Inputs.h"
#include "Engine/Utilitaries/Log.h"

#include "Engine/3D/Camera.h"
#include "Game3D/Scenes/Scene_Test.h"

Player3D::Player3D() :
    Actor()
{
    mName = "Player";
}

Player3D::~Player3D()
{
}

void Player3D::Start()
{
    pCamera = dynamic_cast<Camera*>(AddComponent(new Camera(this)));
    pCamera->getLocalTransform()->addRotationZ(180.0f);
    pCamera->getLocalTransform()->addLocationX(0.15f);
    pCamera->getLocalTransform()->addLocationZ(-0.2f);
    Actor::Start();
}

void Player3D::Update(const float _deltaTime)
{
    Actor::Update(_deltaTime);
    
    if (Inputs::GetKey(SDLK_z))
    {
        mTransform3D.addLocation(pCamera->getLocalTransform()->Forward() * 1 * _deltaTime);
    }

    if (Inputs::GetKey(SDLK_s))
    {
        mTransform3D.addLocation(pCamera->getLocalTransform()->Forward() * -1 * _deltaTime);
    }

    if (Inputs::GetKey(SDLK_q))
    {
        mTransform3D.addLocation(pCamera->getLocalTransform()->Right() * -1 * _deltaTime);
    }

    if (Inputs::GetKey(SDLK_d))
    {
        mTransform3D.addLocation(pCamera->getLocalTransform()->Right() * 1 * _deltaTime);
    }
    
    /*if (Inputs::GetKeyDown(SDLK_r))
    {
        getScene()->getGame()->SetScene<Scene_Test>();
    }*/
    
    //Rotation is stocked in a vector before being transformed to quat via ZYX order
    const float pitch = Inputs::GetMouseDeltaY() * 10.0f * _deltaTime;
    const float yaw = Inputs::GetMouseDeltaX() * 10.0f * _deltaTime;
    
    pCamera->getLocalTransform()->addRotationZ(yaw);
    pCamera->getLocalTransform()->addRotationY(pitch);
    pCamera->getLocalTransform()->clampRotationY(-89.0f, 89.0f);
    pCamera->getLocalTransform()->computeRotation();
}

void Player3D::Destroy()
{
    Actor::Destroy();
}
