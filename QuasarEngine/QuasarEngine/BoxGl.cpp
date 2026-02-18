#include "BoxGl.h"
#include "Assets.h"

#include "Object.h"
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
	AddComponent(new Object(this, t, 1));
	Actor::Start();
}

void BoxGl::Update(float deltaTime)
{
	Actor::Update(deltaTime);
	mTransform3D.rotateAroundY(deltaTime);
}

void BoxGl::Destroy()
{
	Actor::Destroy();
}
