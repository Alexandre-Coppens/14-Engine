#include "Paddle.h"
#include "Inputs.h"
#include "Assets.h"

#include "cBoxCollider2D.h"
#include "cAnimation2D.h"

Paddle::Paddle():
	Actor()
{
	mName = "Paddle";
	mTransform.setSize({ 51,51 });
}

Paddle::~Paddle()
{
}

void Paddle::Start()
{
	std::vector<Texture*> textureList;
	textureList.push_back(&Assets::GetTexture("00_megaman"));
	textureList.push_back(&Assets::GetTexture("01_megaman"));
	textureList.push_back(&Assets::GetTexture("02_megaman"));
	textureList.push_back(&Assets::GetTexture("03_megaman"));
	textureList.push_back(&Assets::GetTexture("04_megaman"));
	textureList.push_back(&Assets::GetTexture("05_megaman"));
	textureList.push_back(&Assets::GetTexture("06_megaman"));
	textureList.push_back(&Assets::GetTexture("07_megaman"));

	AddComponent(new BoxCollider2D(this, 0, Rectangle{ Vector2Zero(), Vector2{ 50.0f, 50.0f } }));
	AddComponent(new AnimatedSprite2D(this, textureList, 0));

	Actor::Start();

	mTransform.setLocation(Vector2{375, 700});
}

void Paddle::Update(float _deltaTime)
{
	Vector2 oldPos = mTransform.getLocation();

	if (Inputs::GetKey(SDLK_q))
	{
		mTransform.addLocationX(-500 * _deltaTime);
	}

	if (Inputs::GetKey(SDLK_d))
	{
		mTransform.addLocationX(500 * _deltaTime);
	}

	Actor::Update(_deltaTime);

	Component* c = GetComponent("BoxCollider2D");
	if (c == nullptr) return;
	BoxCollider2D* bc = dynamic_cast<BoxCollider2D*>(c);
	if (bc == nullptr) return;
	if (bc->getIsColliding())
	{
		mTransform.setLocation(oldPos);
	}
}

void Paddle::Destroy()
{
	Actor::Destroy();
}
