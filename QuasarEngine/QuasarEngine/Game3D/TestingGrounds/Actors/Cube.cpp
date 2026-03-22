#include "Cube.h"

//#include "Engine/3D/cBoxCollider.h"
#include "Engine/3D/cBoxCollider.h"
#include "Engine/Utilitaries/Assets.h"

#include "Engine/3D/Mesh.h"
#include "Engine/Utilitaries/Time.h"

Cube::Cube(std::string _name, std::string _model, std::string _texture, std::string _shader) :
	Actor()
{
	mName = _name;
	mModelName = _model;
	mTextureName = _texture;
	mShaderName = _shader;
}

Cube::~Cube()
{
}

void Cube::Start()
{
	mModel = dynamic_cast<Model*>(AddComponent(new Model(this, mShaderName)));
	mModel->setMesh(Assets::GetMesh(mModelName));
	mModel->getMesh()->AddTexture(Assets::GetTexture(mTextureName));

	mCollider = dynamic_cast<BoxCollider*>(AddComponent(new BoxCollider(this)));
	dynamic_cast<BoxCollider*>(mCollider)->setSize(1.0f);
	Actor::Start();
}

void Cube::Update(const float _deltaTime)
{
	mTime += _deltaTime;
	mModel->setColor(Vector4(1.0f, Cos(mTime), 1.0f, 1.0f));
	Actor::Update(_deltaTime);
}

void Cube::Destroy()
{
	Actor::Destroy();
	mModel = nullptr;
	//mCollider = nullptr;
}
