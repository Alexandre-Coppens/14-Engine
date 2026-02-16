#include "BoxGl.h"
#include "Assets.h"

#include "cBoxCollider2D.h"
#include "cSprite2D.h"

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
	AddComponent(new Sprite2D(this, Assets::GetTexture("Block"), 0));
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
