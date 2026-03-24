#include "Paddle.h"
#include "Engine/Utilitaries/Managers/Inputs.h"
#include "Engine/Utilitaries/Assets.h"
#include "Engine/Scene.h"
#include "Engine/Game.h"

#include "Engine/2D/BoxCollider2D.h"
#include "Engine/2D/Animation2D.h"
#include "Engine/2D/Gravity2D.h"
#include "Game2D/Scenes/Scene_Pong.h"
#include "Game2D/Scenes/Scene_GameOver.h"

Paddle::Paddle():
	Actor()
{
	mName = "Paddle";
	mTransform2D->setSize({ 51,51 });
}

Paddle::~Paddle()
{
}

void Paddle::Start()
{
	std::vector<GENERATED_TEXTURE> animation {PNG_00_megaman, PNG_01_megaman, PNG_02_megaman, PNG_03_megaman, PNG_04_megaman, PNG_05_megaman, PNG_06_megaman, PNG_07_megaman};
	AddComponent(new BoxCollider2D(this, 1, CollisionPurpose::Block, Rectangle{ Vector2Zero(),  Vector2{ 50.0f, 50.0f } }));
	AddComponent(new AnimatedSprite2D(this, Assets::GetTextures(animation), 0));
	AddComponent(new Gravity2D(this, 0));

	Actor::Start();
}

void Paddle::Update(float _deltaTime)
{
	Actor::Update(_deltaTime);
	Gravity2D* gravity = GetComponent<Gravity2D>();

	if (Inputs::GetKey(SDLK_q))
	{
		gravity->setVelocity(gravity->getVelocity() + MultiplyScalar(mTransform2D->Right(), -500 * _deltaTime));
		GetComponent<Sprite2D>()->setXFlip(true);
	}

	if (Inputs::GetKey(SDLK_d))
	{
		gravity->setVelocity(gravity->getVelocity() + MultiplyScalar(mTransform2D->Right(), 500 * _deltaTime));
		GetComponent<Sprite2D>()->setXFlip(false);
	}

	if (Inputs::GetKeyDown(SDLK_SPACE))
	{
		Log::Info(gravity->isTouchingFloor ? "true" : "false");
		if(gravity->isTouchingFloor) gravity->setVelocity(gravity->getVelocity() + MultiplyScalar(mTransform2D->Up(), 500));
	}

	if (getTransform2D()->getLocation().y > 850)
	{
		getTransform2D()->setLocation(Vector2{ 200, 500 });
		life--;
		if (dynamic_cast<Scene_Pong*>(getScene()) != nullptr)
		{
			if (life == 0)
			{
				getScene()->getGame()->SetScene<Scene_GameOver>();
			}
		}
		else
		{
			getScene()->getGame()->SetScene<Scene_Pong>();
		}
	}
}

void Paddle::Destroy()
{
	Actor::Destroy();
}
