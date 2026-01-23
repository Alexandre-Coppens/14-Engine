#include "Box.h"

#include "cBoxCollider2D.h"

Box::Box(Scene* _pScene) :
	Actor(_pScene)
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
