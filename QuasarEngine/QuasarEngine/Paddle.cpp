#include "Paddle.h"
#include "Inputs.h"

#include "cBoxCollider2D.h"

Paddle::Paddle(Scene* _pScene):
	Actor(_pScene)
{
	sName = "Paddle";
	AddComponent(new BoxCollider2D(this, 0, Rectangle{ Vector2Zero(), Vector2{ 50.0f, 50.0f } }));
	transform.location = Vector2{ 375, 700 };
}

Paddle::~Paddle()
{
}

void Paddle::Start()
{
	Actor::Start();
}

void Paddle::Update(float deltaTime)
{
	Vector2 oldPos = transform.location;

	if (Inputs::GetKey(SDLK_q))
	{
		transform.location.x -= 500 * deltaTime;
	}

	if (Inputs::GetKey(SDLK_d))
	{
		transform.location.x += 500 * deltaTime;
	}

	Actor::Update(deltaTime);

	Component* c = GetComponent("BoxCollider2D");
	if (c == nullptr) return;
	BoxCollider2D* bc = dynamic_cast<BoxCollider2D*>(c);
	if (bc == nullptr) return;
	if (bc->GetIsColliding())
	{
		transform.location = oldPos;
	}
}

void Paddle::Destroy()
{
	Actor::Destroy();
}
