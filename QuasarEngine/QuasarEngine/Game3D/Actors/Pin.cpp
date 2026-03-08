#include "Pin.h"

#include "Engine/Utilitaries/Assets.h"

#include "Engine/3D/cModel.h"
#include "Engine/3D/Mesh.h"
#include "Engine/3D/cBoxCollider.h"
#include "Engine/3D/cPhysicBody.h"
#include "Engine/Utilitaries/Inputs.h"
#include "Engine/Utilitaries/Log.h"

Pin::Pin() :
    Actor()
{
    mName = "Pin";
}

Pin::~Pin()
{
}

void Pin::Start()
{
    mModel = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
    mPhysicBody = dynamic_cast<PhysicBody*>(AddComponent(new PhysicBody(this, ColliderType::BOX)));
    BoxCollider* collider = dynamic_cast<BoxCollider*>(mPhysicBody->getReferencedCollider());
    
    mPhysicBody->setMass(1.6f);
    
    collider->setOffset(Vector3{0.0f, 0.0f, 0.015f});
    collider->setSize(Vector3{0.01f, 0.01f, 0.03f});
    
    mModel->setMesh(Assets::GetMesh("Pin"));
    mModel->getMesh()->AddTexture(Assets::GetTexture("Pin"));
    Actor::Start();
}

void Pin::Update(const float _deltaTime)
{
    Log::Info(ToString(mTransform3D.getRotation()));
    Actor::Update(_deltaTime);
    
}

void Pin::Destroy()
{
    Actor::Destroy();
}
