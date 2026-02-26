#include "Ball.h"

#include "Engine/Utilitaries/Assets.h"

#include "Engine/cModel.h"
#include "Engine/Mesh.h"

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
    mModel->setMesh(Assets::GetMesh("Ball"));
    mModel->getMesh()->AddTexture(Assets::GetTexture("Ball"));
    Actor::Start();
}

void Ball::Update(const float _deltaTime)
{
    Actor::Update(_deltaTime);
}

void Ball::Destroy()
{
    Actor::Destroy();
}
