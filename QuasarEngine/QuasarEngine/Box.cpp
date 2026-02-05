#include "Box.h"
#include "Assets.h"

#include "cBoxCollider2D.h"
#include "cSprite2D.h"

Box::Box():
	Actor()
{
	mName = "Box";
	mTransform.setLocation(Vector2{ 100, 700 });
	mTransform.setSize(Vector2{ 50, 50 });
}

Box::~Box()
{
}

void Box::Start()
{
	AddComponent(new Sprite2D(this, Assets::GetTexture("Block"), 0));
	AddComponent(new BoxCollider2D(this, 0, Rectangle{ Vector2Zero(), mTransform.getSize() }));

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
