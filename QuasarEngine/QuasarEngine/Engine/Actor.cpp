#include "Actor.h"

#include "Engine/Utilitaries/Log.h"

#include "Engine/Component.h"
#include "Engine/Scene.h"

Actor::Actor():
	pScene(Scene::ActiveScene),
	mState(ActorState::Active),
	mTransform2D(Transform2D()),
	mTransform3D(Transform3D())
{
}

Actor::~Actor()
{
	Actor::Destroy();
}

void Actor::Start()
{
	for (Component* c : mComponentList) c->OnActorStart();
	Log::Info("Actor::" + mName + "::Started");
}

void Actor::Update(const float _deltaTime)
{
	for (const auto c : mComponentList)
	{
		c->Update(_deltaTime);
	}
}

void Actor::Destroy()
{
	pScene = nullptr;
	for (const auto c : mComponentList)
	{
		Log::Info("Removing Component: " + c->getName());
		c->OnEnd();
	}
	RemoveComponents();
}

Component* Actor::AddComponent(Component* _c)
{
	const int componentUpdateOrder = _c->getUpdateOrder();
	std::vector<Component*>::iterator it;
	for (it = mComponentList.begin(); it != mComponentList.end(); it++)
	{
		if (componentUpdateOrder < (*it)->getUpdateOrder()) break;
	}
	mComponentList.insert(it, _c);
	_c->OnStart();
	return _c;
}

void Actor::RemoveComponents()
{
	for (Component* c : mComponentList)
	{
		delete c;
		c = nullptr;
	}
	mComponentList.clear();
}