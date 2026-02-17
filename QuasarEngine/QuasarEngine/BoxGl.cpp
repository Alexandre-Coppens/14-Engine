#include "BoxGl.h"
#include "Assets.h"

#include "Material.h"
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
	AddComponent(new Material(this, t, 1));
	Actor::Start();
}

void BoxGl::Update(float deltaTime)
{
	Actor::Update(deltaTime);
	mTransform3D.setScale(mTransform3D.getScale() * cos(Time::currentFrameTime * 5));
}

void BoxGl::Destroy()
{
	Actor::Destroy();
}
