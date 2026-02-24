#include "Coin.h"
#include "Engine/Utilitaries/Assets.h"

#include "Engine/cBoxCollider2D.h"
#include "Engine/cAnimation2D.h"
#include "Engine/Scene.h"

Coin::Coin() :
	Actor()
{
	mName = "Coin";
	mTransform2D.setSize({ 51,51 });
}

Coin::~Coin()
{
}

void Coin::Start()
{
	AddComponent(new BoxCollider2D(this, 1, CollisionPurpose::Overlapp, Rectangle{ Vector2Zero(),  Vector2{ 50.0f, 50.0f } }));
	AddComponent(new AnimatedSprite2D(this, Assets::GetTextures("coin"), 0));

	Actor::Start();
}

void Coin::Update(float _deltaTime)
{
	Actor::Update(_deltaTime);
	if (GetComponent<BoxCollider2D>()->getContinuedCollision())
	{
		getScene()->DeleteActor(this);
	}
}

void Coin::Destroy()
{
	Actor::Destroy();
}
