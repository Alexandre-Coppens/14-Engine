#include "Box.h"
#include "Engine/Utilitaries/Assets.h"

#include "Engine/2D/BoxCollider2D.h"
#include "Engine/2D/Sprite2D.h"

Box::Box():
	Actor()
{
	mName = "Box";
	mTransform2D->setLocation(Vector2{ 100, 700 });
	mTransform2D->setSize(Vector2{ 50, 50 });
}

Box::~Box()
{
	Actor::~Actor();
}

void Box::Start()
{
	AddComponent(new Sprite2D(this, Assets::GetTexture("Block"), 0));
	AddComponent(new BoxCollider2D(this, 0, CollisionPurpose::Block, Rectangle{ Vector2Zero(), mTransform2D->getSize() }));

	Actor::Start();
}

void Box::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
}

void Box::Destroy()
{
	Actor::Destroy();
}
