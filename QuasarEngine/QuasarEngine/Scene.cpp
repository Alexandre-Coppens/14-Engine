#include "Scene.h"

#include "Actor.h"
#include "Assets.h"
#include "Log.h"

Scene* Scene::ActiveScene = nullptr;

Scene::Scene(std::string _name):
	mName(std::move(_name)),
	pRenderer(nullptr),
	pGame(nullptr)
{
}

Scene::~Scene() {}

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
	for (Actor* a : mAddActorList)
	{
		DeleteActor(a);
	}
	mAddActorList.clear();
	
	for (Actor* a : mActorList)
	{
		DeleteActor(a);
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