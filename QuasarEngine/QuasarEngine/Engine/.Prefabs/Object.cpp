#include "Object.h"

//#include "Engine/3D/cBoxCollider.h"
#include "Engine/3D/cBoxCollider.h"
#include "Engine/3D/Mesh.h"

Object::Object(std::string _name, GENERATED_MESHES _model, GENERATED_TEXTURE _texture, std::string _shader):
    Actor()
{
    mName = _name;
    mMesh = _model;
    mTexture = _texture;
    mShaderName = _shader;
    Initialize();
}

Object::~Object()
{
}

void Object::Initialize()
{
    mModel = dynamic_cast<Model*>(AddComponent(new Model(this, mShaderName)));
    mCollider = dynamic_cast<BoxCollider*>(AddComponent(new BoxCollider(this)));
    Actor::Initialize();
}

void Object::Start()
{
    mModel->setMesh(Assets::GetMesh(mMesh));
    mModel->getMesh()->AddTexture(Assets::GetTexture(mTexture));
    
    //dynamic_cast<BoxCollider*>(mCollider)->setSize(1.1f);
    Actor::Start();
}

void Object::Update(const float _deltaTime)
{
    Actor::Update(_deltaTime);
}

void Object::Destroy()
{
    Actor::Destroy();
    mModel = nullptr;
    //mCollider = nullptr;
}
