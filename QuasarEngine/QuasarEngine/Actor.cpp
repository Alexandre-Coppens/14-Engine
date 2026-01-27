#include "Actor.h"
#include "Log.h"

#include "Component.h"
#include "Scene.h"

Actor::Actor() :
	mState(ActorState::Active), mTransform(Transform2D()), pScene(Scene::sActiveScene)
{
}

Actor::~Actor()
{
}

void Actor::Start()
{
	for(const auto c : mComponentList)
	{
		c.second->OnStart();
	}
}

void Actor::Update(float _deltaTime)
{
	for (const auto c : mComponentList)
	{
		c.second->Update();
	}
}

void Actor::Destroy()
{
	for (const auto c : mComponentList)
	{
		c.second->OnEnd();
	}
}

void Actor::AddComponent(Component* _c)
{
	if (GetComponent(_c->getName()) == nullptr) mComponentList[_c->getName()] = _c;
	else
	{
		Log::Info(mName + ": Has replaced " + _c->getName() + " Component by a new one with 'ADD' Function.");
		Component* oldComponent;
		oldComponent = mComponentList[_c->getName()];
		delete oldComponent;
		oldComponent = nullptr;
		mComponentList[_c->getName()] = _c;
	}
	_c->OnStart();
}

void Actor::RemoveComponent(std::string _c)
{
	if (mComponentList.find(_c) == mComponentList.end())
	{
		Log::Info(mName + ": No Instance of " + _c + " Component found to remove.");
		return;
	}
	delete mComponentList[_c];
	mComponentList[_c] = nullptr;
}

