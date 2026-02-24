#include "BoxGl.h"
#include "Assets.h"

#include "cModel.h"
#include "Mesh.h"
#include "Time.h"

BoxGl::BoxGl() :
	Actor()
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
	//mTransform3D.rotateAroundY(_deltaTime * 0.3f);
	//mTransform3D.setLocationZ(cos(Time::currentFrameTime * 0.0005f));
	mTransform3D.ComputeWorldTransform();
}

void BoxGl::Destroy()
{
	Actor::Destroy();
}
