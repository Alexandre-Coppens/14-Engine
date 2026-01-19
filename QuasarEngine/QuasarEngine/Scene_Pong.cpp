#include "Scene_Pong.h"
#include "Log.h"

#include "Paddle.h"

Scene_Pong::Scene_Pong(std::string _sName):
	Scene(_sName)
{
}

void Scene_Pong::Start()
{
	Scene::Start();
	Log::Info("GAME: Loading Scene: '" + sName + "'.");
	vActorList.push_back(new Paddle(this));
}

void Scene_Pong::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Scene_Pong::Render()
{
	Scene::Render();
}

void Scene_Pong::Close()
{
}
