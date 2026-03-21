#include "Actor.h"

#include "Engine/Utilitaries/Log.h"

#include "Engine/Component.h"
#include "Engine/Scene.h"
#include "Utilitaries/DebugMemoryLeakCatcher.h"

Actor::Actor():
	mScene(Scene::ActiveScene),
	mState(ActorState::Active),
	mTransform2D(nullptr),
	mTransform3D(nullptr)
{
	DEBUGAddClass("Actor");
}

Actor::~Actor() = default;

void Actor::Start()
{
	mTransform2D = dynamic_cast<Transform2D*>(AddComponent(new Transform2D()));
	mTransform3D = dynamic_cast<Transform3D*>(AddComponent(new Transform3D(this, WORLD)));
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
	mScene = nullptr;
	for (const auto component : mComponentList)
	{
		component->Destroy();
	}
	RemoveComponents();
	DEBUGRemoveClass("Actor");
}

Component* Actor::AddComponent(Component* _component)
{
	const int componentUpdateOrder = _component->getUpdateOrder();
	std::vector<Component*>::iterator it;
	for (it = mComponentList.begin(); it != mComponentList.end(); it++)
	{
		if (componentUpdateOrder < (*it)->getUpdateOrder()) break;
	}
	mComponentList.insert(it, _component);
	_component->OnStart();
	return _component;
}

void Actor::RemoveComponents()
{
	for (Component* component : mComponentList)
	{
		delete component;
		component = nullptr;
	}
	mComponentList.clear();
}