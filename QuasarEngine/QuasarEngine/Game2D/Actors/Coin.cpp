#include "Coin.h"
#include "Engine/Utilitaries/Assets.h"

#include "Engine/2D/BoxCollider2D.h"
#include "Engine/2D/Animation2D.h"
#include "Engine/Scene.h"

Coin::Coin() :
	Actor()
{
	mName = "Coin";
	mTransform2D->setSize({ 51,51 });
}

Coin::~Coin()
{
}

void Coin::Start()
{
	std::vector<GENERATED_TEXTURE> animation {PNG_Coin_01, PNG_Coin_02, PNG_Coin_03, PNG_Coin_04, PNG_Coin_05, PNG_Coin_06};
	AddComponent(new BoxCollider2D(this, 1, CollisionPurpose::Overlapp, Rectangle{ Vector2Zero(),  Vector2{ 50.0f, 50.0f } }));
	AddComponent(new AnimatedSprite2D(this, Assets::GetTextures(animation), 0));

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
