#include "Object.h"

//#include "Engine/3D/cBoxCollider.h"
#include "Engine/3D/cBoxCollider.h"
#include "Engine/Utilitaries/Assets.h"

#include "Engine/3D/Mesh.h"

Object::Object(std::string _name, std::string _model, std::string _texture, std::string _shader) :
    Actor()
{
    mName = _name;
    mModelName = _model;
    mTextureName = _texture;
    mShaderName = _shader;
}

Object::~Object()
{
}

void Object::Start()
{
    mModel = dynamic_cast<Model*>(AddComponent(new Model(this, mShaderName)));
    mModel->setMesh(Assets::GetMesh(OBJ_cube));
    mModel->getMesh()->AddTexture(Assets::GetTexture(PNG_Block));

    mCollider = dynamic_cast<BoxCollider*>(AddComponent(new BoxCollider(this)));
    dynamic_cast<BoxCollider*>(mCollider)->setSize(1.1f);
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
