#include "Scene.h"

#include "Renderer.h"
#include "Actor.h"
#include "Assets.h"

Scene* Scene::ActiveScene = nullptr;

Scene::Scene(std::string _sName):
	sName(_sName)
{
}

void Scene::Start()
{
	ActiveScene = this;
}

//Update Before Inputs
void Scene::EarlyUpdate()
{
	for(Actor* a : vAddActorList)
	{
		a->Start();
		vActorList.push_back(a);
		a = nullptr;
	}
	vAddActorList.clear();
}

void Scene::Update(float deltaTime)
{
	for (Actor* actor : vActorList)
	{
		actor->Update(deltaTime);
	}
}

//Update After Rendering
void Scene::LateUpdate()
{
}

void Scene::Close()
{
	for (Actor* a : vAddActorList)
	{
		DeleteActor(a);
	}
	KillActors();
}

void Scene::AddActor(Actor* actor)
{
	vAddActorList.push_back(actor);
}

void Scene::DeleteActor(Actor* actor)
{
	vActorList.erase(std::remove(vActorList.begin(), vActorList.end(), actor), vActorList.end());
	vDestroyActorList.push_back(actor);
}

void Scene::KillActors()
{
	for(Actor* a : vDestroyActorList)
	{
		delete a;
	}
	vDestroyActorList.clear();
}

void Scene::Load()
{
	Start();
}

void Scene::UnLoad()
{
	while (!vActorList.empty())
	{
		delete vActorList.back();
	}
	Assets::Clear();
}