#include "BoxGl.h"
#include "Assets.h"

#include "cModel.h"
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
	Texture* t = Assets::GetTexture("Block");
	AddComponent(new Model(this));
	Actor::Start();
}

void BoxGl::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
	mTransform3D.rotateAroundX(_deltaTime * 1);
	mTransform3D.rotateAroundY(_deltaTime * 0.3);
	mTransform3D.setLocationZ(cos(Time::currentFrameTime * 0.0005f));
	mTransform3D.ComputeWorldTransform();
}

void BoxGl::Destroy()
{
	Actor::Destroy();
}
