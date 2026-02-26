#include "Ball.h"

#include "Engine/Utilitaries/Assets.h"

#include "Engine/cModel.h"
#include "Engine/cPhysic.h"
#include "Engine/Mesh.h"
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
    AddComponent(new Physic(this));
    
    mModel->setMesh(Assets::GetMesh("Ball"));
    mModel->getMesh()->AddTexture(Assets::GetTexture("Ball"));
    Actor::Start();
}

void Ball::Update(const float _deltaTime)
{
    Actor::Update(_deltaTime);
    Log::Info(ToString(mTransform3D.getLocation()));
}

void Ball::Destroy()
{
    Actor::Destroy();
}
