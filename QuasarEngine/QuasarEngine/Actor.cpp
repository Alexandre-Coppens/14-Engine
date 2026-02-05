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
}

void Actor::Update(float _deltaTime)
{
	for (const auto c : mComponentList)
	{
		c->Update(_deltaTime);
	}
}

void Actor::Destroy()
{
	for (const auto c : mComponentList)
	{
		c->OnEnd();
	}
	RemoveComponents();
}

void Actor::AddComponent(Component* _c)
{
	mComponentList.push_back(_c);
	_c->OnStart();
}

void Actor::RemoveComponents()
{
	for (Component* c : mComponentList)
	{
		delete c;
	}
	mComponentList.clear();
}

