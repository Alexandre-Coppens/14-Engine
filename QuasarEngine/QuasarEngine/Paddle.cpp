#include "Paddle.h"
#include "Inputs.h"

Paddle::Paddle(Scene* _pScene):
	Actor(_pScene)
{
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
	Actor::Update(deltaTime);

	if (Inputs::GetKey(SDLK_q)) 
	{
		transform.location.x -= 500 * deltaTime;
	}

	if (Inputs::GetKey(SDLK_d))
	{
		transform.location.x += 500 * deltaTime;
	}
}

void Paddle::Destroy()
{
	Actor::Destroy();
}
