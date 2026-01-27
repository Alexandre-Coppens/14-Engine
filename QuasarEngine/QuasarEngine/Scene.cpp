#include "Scene.h"

#include "Renderer.h"
#include "Actor.h"
#include "Assets.h"

Scene* Scene::sActiveScene = nullptr;

Scene::Scene(std::string _name):
	mName(_name)
{
}

void Scene::Start()
{
	sActiveScene = this;
}

//Update Before Inputs
void Scene::EarlyUpdate()
{
	for(Actor* a : mAddActorList)
	{
		a->Start();
		mActorList.push_back(a);
		a = nullptr;
	}
	mAddActorList.clear();
}

void Scene::Update(float deltaTime)
{
	for (Actor* actor : mActorList)
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
	for (Actor* a : mAddActorList)
	{
		DeleteActor(a);
	}
	KillActors();
}

void Scene::AddActor(Actor* actor)
{
	mAddActorList.push_back(actor);
}

void Scene::DeleteActor(Actor* actor)
{
	mActorList.erase(std::remove(mActorList.begin(), mActorList.end(), actor), mActorList.end());
	mDestroyActorList.push_back(actor);
}

void Scene::KillActors()
{
	for(Actor* a : mDestroyActorList)
	{
		delete a;
	}
	mDestroyActorList.clear();
}

void Scene::Load()
{
	Start();
}

void Scene::UnLoad()
{
	while (!mActorList.empty())
	{
		delete mActorList.back();
	}
	Assets::Clear();
}