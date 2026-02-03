#include "Floor.h"
#include "Assets.h"

#include "cBoxCollider2D.h"
#include "cSprite2D.h"

Floor::Floor() :
	Actor()
{
	mName = "Floor";
	mTransform.setLocation(Vector2{ 400, 750});
	mTransform.setSize(Vector2{ 500, 25});
	AddComponent(new BoxCollider2D(this, 0, Rectangle{ Vector2Zero(), mTransform.getSize()}));
}

Floor::~Floor()
{
}

void Floor::Start()
{
	AddComponent(new Sprite2D(this, Assets::GetTexture("ball"), 0));

	Actor::Start();
}

void Floor::Update(float deltaTime)
{
	Actor::Update(deltaTime);
}

void Floor::Destroy()
{
	Actor::Destroy();
}
