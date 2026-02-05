#include "Scene.h"

#include "RendererSdl.h"
#include "Actor.h"
#include "Assets.h"
#include "Log.h"

Scene* Scene::sActiveScene = nullptr;

Scene::Scene(std::string _name):
	mName(_name)
{
}

void Scene::Start()
{
	sActiveScene = this;
	Log::Info("GAME: Loading Scene: '" + mName + "'.");
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
		if (mActorList.size() == 0) return;
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

Actor* Scene::AddActor(Actor* actor)
{
	mAddActorList.push_back(actor);
	return actor;
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
		a->Destroy();
		delete a;
	}
	mDestroyActorList.clear();
}

void Scene::Load(Game* _pGame)
{
	pGame = _pGame;
	Start();
}

void Scene::UnLoad()
{
	while (!mActorList.empty())
	{
		mActorList.back()->Destroy();
		delete mActorList.back();
		mActorList.pop_back();
	}
	Assets::Clear();
}