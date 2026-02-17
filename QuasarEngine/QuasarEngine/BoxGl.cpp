#include "BoxGl.h"
#include "Assets.h"

#include "Material.h"

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
	AddComponent(new Material(this, t, 0));
	Actor::Start();
}

void BoxGl::Update(float deltaTime)
{
	Actor::Update(deltaTime);
}

void BoxGl::Destroy()
{
	Actor::Destroy();
}
