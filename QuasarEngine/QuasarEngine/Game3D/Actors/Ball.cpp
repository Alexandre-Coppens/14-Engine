#include "Ball.h"

#include "Engine/3D/cSphereCollider.h"
#include "Engine/3D/Camera.h"
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
    mPhysicBody = dynamic_cast<PhysicBody*>(AddComponent(new PhysicBody(this, ColliderType::SPHERE)));
    mCamera = dynamic_cast<Camera*>(AddComponent(new Camera(this)));
    SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(mPhysicBody->getReferencedCollider());
    
    mPhysicBody->setMass(7.3f);
    mCamera->getLocalTransform()->setLocation(Vector3{0.1f, 0.0f, 0.1f});
    mCamera->getLocalTransform()->addRotationZ(180.0f);
    
    sphereCollider->setRadius(0.01f);
    sphereCollider->setFriction(0.05f);
    
    mModel->setMesh(Assets::GetMesh("Ball"));
    mModel->getMesh()->AddTexture(Assets::GetTexture("Ball"));
    Actor::Start();
}

void Ball::Update(const float _deltaTime)
{
    Actor::Update(_deltaTime);
    //if (Inputs::GetKey(SDLK_UP)) mPhysicBody->addVelocityX(-1 * _deltaTime);
    //if (Inputs::GetKey(SDLK_DOWN)) mPhysicBody->addVelocityX(1 * _deltaTime);
    if (Inputs::GetKey(SDLK_a) && !mLaunched)    mTransform3D.addLocationY(0.1f * _deltaTime);
    if (Inputs::GetKey(SDLK_e) && !mLaunched)   mTransform3D.addLocationY(-0.1f * _deltaTime);
    if (Inputs::GetKeyDown(SDLK_SPACE) && !mLaunched)
    {
        mLaunched = true;
        mPhysicBody->setVelocity(Vector3{-1, 0, 0});
    }
    if (Inputs::GetKeyDown(SDLK_r))
    {
        mLaunched = false;
        mTransform3D.setLocation(Vector3{0, 0, -0.2f});
        mPhysicBody->setVelocity(Vector3{0, 0, 0});
    }
    if (!mLaunched)
    {
        mTransform3D.setLocationY(Clamp(mTransform3D.getLocation().y, -0.05f, 0.05f));
    }
    Log::Info(ToString(mTransform3D.getRotation()));
}

void Ball::Destroy()
{
    Actor::Destroy();
}
