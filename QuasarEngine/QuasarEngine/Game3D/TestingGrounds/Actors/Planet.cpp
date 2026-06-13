#include "Planet.h"

#include "Engine/Utilitaries/Assets.h"
#include "Engine/Utilitaries/MathLib.h"

#include "Engine/3D/Mesh.h"

Planet::Planet(GENERATED_MESHES _mesh, GENERATED_SHADER_PROGRAMS _shader, GENERATED_TEXTURE _texture, float _selfRotationSpeed, Actor* _center, float _rotateAroundSpeed) :
    Actor()
{
    mName = "Planet";
    mShader = _shader;
    mTexture = _texture;
    mMesh = _mesh;
    mConstantRotation = _selfRotationSpeed;
    mCenterActor = _center;
    mRotateAroundSpeed = _rotateAroundSpeed;
    Initialize();
}

Planet::~Planet()
{
}

void Planet::Initialize()
{
    mModel = dynamic_cast<Model*>(AddComponent(new Model(this, mShader)));
    Actor::Initialize();
}

void Planet::Start()
{
    mModel->setMesh(Assets::GetMesh(mMesh));
    mModel->getMaterial()->SetTexture("uTexture", Assets::GetTexture(mTexture));
    
    mDistanceToCenter = Distance(getTransform3D()->getLocation(), mCenterActor->getTransform3D()->getLocation());
    
    Actor::Start();
}

void Planet::Update(const float _deltaTime)
{
    Vector3 centerPos = mCenterActor->getTransform3D()->getLocation();
    mRotationPosition += mRotateAroundSpeed * _deltaTime;
    getTransform3D()->setLocation(Vector3(centerPos.x + sin(mRotationPosition) * mDistanceToCenter, centerPos.y + cos(mRotationPosition) * mDistanceToCenter, 0.0f));
    getTransform3D()->addRotationZ(mConstantRotation * _deltaTime);
    Actor::Update(_deltaTime);
}

void Planet::Destroy()
{
    Actor::Destroy();
}
