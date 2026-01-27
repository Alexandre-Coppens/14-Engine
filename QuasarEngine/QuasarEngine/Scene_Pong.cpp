#include "Scene_Pong.h"
#include "Log.h"
#include "Assets.h"

#include "Paddle.h"
#include "Box.h"

Scene_Pong::Scene_Pong(std::string _name):
	Scene(_name)
{
}

void Scene_Pong::Start()
{
	Scene::Start();
	Log::Info("GAME: Loading Scene: '" + mName + "'.");

	Assets::LoadTexture(*pRenderer, "Ressources/pokeball.png", "ball");

	AddActor(new Paddle());
	AddActor(new Box());
}

void Scene_Pong::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Scene_Pong::Close()
{
}
