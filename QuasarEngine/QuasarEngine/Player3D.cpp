#include "Player3D.h"
#include "Assets.h"

#include "Camera.h"
#include "Inputs.h"
#include "Time.h"

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
    AddComponent(new Camera(this));
    Actor::Start();
}

void Player3D::Update(const float _deltaTime)
{
    Actor::Update(_deltaTime);
    if (Inputs::GetKey(SDLK_z))
    {
        mTransform3D.addLocationX(2 * _deltaTime);
    }

    if (Inputs::GetKey(SDLK_s))
    {
        mTransform3D.addLocationX(-2 * _deltaTime);
    }

    if (Inputs::GetKey(SDLK_q))
    {
        mTransform3D.addLocationY(-2 * _deltaTime);
    }

    if (Inputs::GetKey(SDLK_d))
    {
        mTransform3D.addLocationY(2 * _deltaTime);
    }
}

void Player3D::Destroy()
{
    Actor::Destroy();
}
