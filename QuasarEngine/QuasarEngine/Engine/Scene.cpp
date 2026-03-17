#include "Scene.h"

#include "Engine/Utilitaries/Assets.h"
#include "Engine/Utilitaries/Log.h"

#include "Engine/Actor.h"

Scene* Scene::ActiveScene = nullptr;

Scene::Scene(std::string _name):
	mName(std::move(_name)),
	pRenderer(nullptr),
	pGame(nullptr)
{
}

Scene::~Scene() = default;

void Scene::Start()
{
	ActiveScene = this;
	Log::Info("GAME::Loading Scene: '" + mName + "'.");
}

//Update Before Inputs
void Scene::EarlyUpdate()
{
	InitNewActors();
}

void Scene::Update(const float _deltaTime)
{
	for (Actor* actor : mActorList)
	{
		if (mActorList.empty()) return;
		actor->Update(_deltaTime);
	}
}

//Update After Rendering
void Scene::LateUpdate()
{
}

void Scene::Close()
{
	while (!mAddActorList.empty())
	{
		DeleteActorFromList(&mAddActorList, mAddActorList[0]);
	}
	mAddActorList.clear();
	
	while (!mActorList.empty())
	{
		DeleteActorFromList(&mActorList, mActorList[0]);
	}
	mActorList.clear();

	KillActors();
	pRenderer = nullptr;
	pGame = nullptr;
}

Actor* Scene::AddActor(Actor* actor)
{
	mAddActorList.push_back(actor);
	return actor;
}

void Scene::InitNewActors()
{
	for(Actor* a : mAddActorList)
	{
		a->Start();
		mActorList.push_back(a);
		a = nullptr;
	}
	mAddActorList.clear();
}

void Scene::DeleteActorFromList(std::vector<Actor*>* list, Actor* actor)
{
	list->erase(std::remove(list->begin(), list->end(), actor), list->end());
	mDestroyActorList.push_back(actor);
}

void Scene::DeleteActor(Actor* actor)
{
	mActorList.erase(std::remove(mActorList.begin(), mActorList.end(), actor), mActorList.end());
	mDestroyActorList.push_back(actor);
}

void Scene::KillActors()
{
	for (Actor* a : mDestroyActorList)
	{
		if (a != nullptr)
		{
			a->Destroy();
			delete a;
			a = nullptr;
		}
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
	while (!mAddActorList.empty())
	{
		DeleteActorFromList(&mAddActorList, mAddActorList[0]);
	}
	mAddActorList.clear();
	
	while (!mActorList.empty())
	{
		DeleteActorFromList(&mActorList, mActorList[0]);
	}
	mActorList.clear();

	KillActors();
	Assets::Clear();
}