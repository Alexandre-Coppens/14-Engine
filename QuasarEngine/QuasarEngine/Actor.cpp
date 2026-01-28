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
		c->OnStart();
	}
}

void Actor::Update(float _deltaTime)
{
	for (const auto c : mComponentList)
	{
		c->Update();
	}
}

void Actor::Destroy()
{
	for (const auto c : mComponentList)
	{
		c->OnEnd();
	}
}

void Actor::AddComponent(Component* _c)
{
	mComponentList.push_back(_c);
	_c->OnStart();
}

//Remove All -Type- Components from Actor
//(There is no way now to remove a specific Component so it's all or nothing.)
template<typename T>
void Actor::RemoveComponents()
{
	for (auto it = mComponentList.begin(); it != mComponentList.end(); it++)
	{
		delete* it;
		mComponentList.erase(it);
	}
}

