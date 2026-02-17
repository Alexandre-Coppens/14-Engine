#include "Box.h"
#include "Assets.h"

#include "cBoxCollider2D.h"
#include "cSprite2D.h"

Box::Box():
	Actor()
{
	mName = "Box";
	mTransform2D.setLocation(Vector2{ 100, 700 });
	mTransform2D.setSize(Vector2{ 50, 50 });
}

Box::~Box()
{
}

void Box::Start()
{
	AddComponent(new Sprite2D(this, Assets::GetTexture("Block"), 0));
	AddComponent(new BoxCollider2D(this, 0, CollisionPurpose::Block, Rectangle{ Vector2Zero(), mTransform2D.getSize() }));

	Actor::Start();
}

void Box::Update(float deltaTime)
{
	Actor::Update(deltaTime);
}

void Box::Destroy()
{
	Actor::Destroy();
}
