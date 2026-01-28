#include "Paddle.h"
#include "Inputs.h"
#include "Assets.h"

#include "cBoxCollider2D.h"
#include "cAnimation2D.h"
#include "cGravity2D.h"

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
	AddComponent(new BoxCollider2D(this, 0, Rectangle{ Vector2Zero(), Vector2{ 50.0f, 50.0f } }));
	AddComponent(new AnimatedSprite2D(this, Assets::GetTextures("megaman"), 0));
	AddComponent(new Gravity2D(this, 0));

	Actor::Start();

	mTransform.setLocation(Vector2{375, 700});
}

void Paddle::Update(float _deltaTime)
{
	Vector2 oldPos = mTransform.getLocation();

	if (Inputs::GetKey(SDLK_q))
	{
		mTransform.addLocation(MultiplyScalar(mTransform.Right(), -500 * _deltaTime));
		GetComponent<Sprite2D>()->setXFlip(true);
	}

	if (Inputs::GetKey(SDLK_d))
	{
		mTransform.addLocation(MultiplyScalar(mTransform.Right(), 500 * _deltaTime));
		GetComponent<Sprite2D>()->setXFlip(false);
	}

	Actor::Update(_deltaTime);

	BoxCollider2D* c = GetComponent<BoxCollider2D>();
	if (c == nullptr) return;
	if (c->getIsColliding())
	{
		mTransform.setLocation(oldPos);
	}
}

void Paddle::Destroy()
{
	Actor::Destroy();
}
