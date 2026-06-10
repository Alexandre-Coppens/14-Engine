#include "Planet.h"

#include "Engine/Utilitaries/Assets.h"

#include "Engine/3D/Mesh.h"

Planet::Planet(GENERATED_MESHES _mesh, GENERATED_SHADER_PROGRAMS _shader, GENERATED_TEXTURE _texture, float _constantRotation) :
    Actor()
{
    mName = "Planet";
    mShader = _shader;
    mTexture = _texture;
    mMesh = _mesh;
    mConstantRotation = _constantRotation;
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
    Actor::Start();
}

void Planet::Update(const float _deltaTime)
{
    getTransform3D()->addRotationZ(mConstantRotation * _deltaTime);
    Actor::Update(_deltaTime);
}

void Planet::Destroy()
{
    Actor::Destroy();
}
