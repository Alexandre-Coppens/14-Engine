#include "Scene_GameOver.h"
#include "Engine/Utilitaries/Assets.h"

#include "Game2D/Actors/Paddle.h"
#include "Game2D/Actors/Box.h"
#include "Engine/Render/RendererSdl.h"

Scene_GameOver::Scene_GameOver(std::string _name) :
	Scene(_name)
{
}

void Scene_GameOver::Start()
{
	Scene::Start();

	Actor* player = AddActor(new Paddle());
	Actor* box1 = AddActor(new Box());
	Actor* box2 = AddActor(new Box());
	Actor* box3 = AddActor(new Box());
	Actor* box4 = AddActor(new Box());

	player->getTransform2D()->setLocation(Vector2{ 150, 400 });

	box1->getTransform2D()->setLocation(Vector2{ 400, 150 });
	box1->getTransform2D()->setSize(Vector2{ 800, 300 });

	box2->getTransform2D()->setLocation(Vector2{ 300, 650 });
	box2->getTransform2D()->setSize(Vector2{ 600, 300 });

	box3->getTransform2D()->setLocation(Vector2{ 50, 400 });
	box3->getTransform2D()->setSize(Vector2{ 100, 800 });

	box4->getTransform2D()->setLocation(Vector2{ 750, 400 });
	box4->getTransform2D()->setSize(Vector2{ 100, 800 });
}

void Scene_GameOver::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Scene_GameOver::Close()
{
}
