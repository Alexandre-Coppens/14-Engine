#include "Actor.h"
#include "Log.h"

#include "Component.h"
#include "Scene.h"

Actor::Actor() :
	eState(ActorState::Active), transform(Transform2D()), pScene(Scene::ActiveScene)
{
}

Actor::~Actor()
{
}

void Actor::Start()
{


	for(const auto c : vComponentList)
	{
		c.second->OnStart();
	}
}

void Actor::Update(float deltaTime)
{
	for (const auto c : vComponentList)
	{
		c.second->Update();
	}
}

void Actor::Destroy()
{
	for (const auto c : vComponentList)
	{
		c.second->OnEnd();
	}
}

void Actor::AddComponent(Component* c)
{
	if (GetComponent(c->GetName()) == nullptr) vComponentList[c->GetName()] = c;
	else
	{
		Log::Info(sName + ": Has replaced " + c->GetName() + " Component by a new one with 'ADD' Function.");
		Component* oldComponent;
		oldComponent = vComponentList[c->GetName()];
		delete oldComponent;
		oldComponent = nullptr;
		vComponentList[c->GetName()] = c;
	}
	c->OnStart();
}

void Actor::RemoveComponent(std::string c)
{
	if (vComponentList.find(c) == vComponentList.end())
	{
		Log::Info(sName + ": No Instance of " + c + " Component found to remove.");
		return;
	}
	delete vComponentList[c];
	vComponentList[c] = nullptr;
}

