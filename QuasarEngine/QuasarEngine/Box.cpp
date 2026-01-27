#include "Box.h"
#include "Assets.h"

#include "cBoxCollider2D.h"
#include "cSprite2D.h"

Box::Box():
	Actor()
{
	sName = "Box";
	transform.location = Vector2{ 100, 700 };
	AddComponent(new BoxCollider2D(this, 0, Rectangle{ Vector2Zero(), Vector2{ 50.0f, 50.0f } }));
}

Box::~Box()
{
}

void Box::Start()
{
	AddComponent(new Sprite2D(this, Assets::GetTexture("ball"), { 50.0f, 50.0f }, 0));

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
