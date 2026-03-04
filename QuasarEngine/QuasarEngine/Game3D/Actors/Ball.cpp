#include "Ball.h"

#include "Engine/Utilitaries/Assets.h"

#include "Engine/3D/Mesh.h"
#include "Engine/Utilitaries/Inputs.h"
#include "Engine/Utilitaries/Log.h"

Ball::Ball() :
    Actor()
{
    mName = "Ball";
}

Ball::~Ball()
{
}

void Ball::Start()
{
    mModel = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
    mPhysicBody = dynamic_cast<PhysicBody*>(AddComponent(new PhysicBody(this)));
    mPhysicBody->setGravityEnabled(false);
    
    mModel->setMesh(Assets::GetMesh("Ball"));
    mModel->getMesh()->AddTexture(Assets::GetTexture("Ball"));
    Actor::Start();
}

void Ball::Update(const float _deltaTime)
{
    Actor::Update(_deltaTime);
    //Log::Info(ToString(mTransform3D.getLocation()));
    
    if (Inputs::GetKey(SDLK_UP)) mPhysicBody->addVelocityX(-1 * _deltaTime);
    if (Inputs::GetKey(SDLK_DOWN)) mPhysicBody->addVelocityX(1 * _deltaTime);
    if (Inputs::GetKey(SDLK_LEFT)) mPhysicBody->addVelocityY(1 * _deltaTime);
    if (Inputs::GetKey(SDLK_RIGHT)) mPhysicBody->addVelocityY(-1 * _deltaTime);
    if (Inputs::GetKeyDown(SDLK_r))
    {
        mPhysicBody->setVelocity(Vector3Zero());
        mTransform3D.setLocation(Vector3(0, 0, -0.24f));
    }
}

void Ball::Destroy()
{
    Actor::Destroy();
}
