#include "BoxGl.h"

#include "Engine/Utilitaries/Assets.h"

#include "Engine/3D/cModel.h"
#include "Engine/3D/Mesh.h"

BoxGl::BoxGl() :
	Actor(), mModel(nullptr)
{
	mName = "Box";
}

BoxGl::~BoxGl()
{
}

void BoxGl::Start()
{
	mModel = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
	mModel->setMesh(Assets::GetMesh("Cube"));
	mModel->getMesh()->AddTexture(Assets::GetTexture("Block"));
	Actor::Start();
}

void BoxGl::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
	//mTransform3D.rotateAroundX(_deltaTime * 1);
	mTransform3D.rotateAroundZ(_deltaTime * 90.0f);
	//mTransform3D.setLocationZ(cos(Time::currentFrameTime * 0.0005f));
	mTransform3D.ComputeWorldTransform();
}

void BoxGl::Destroy()
{
	Actor::Destroy();
}
