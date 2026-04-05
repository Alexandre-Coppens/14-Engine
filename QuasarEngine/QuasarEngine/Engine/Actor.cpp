#include "Actor.h"

#include "Engine/Utilitaries/Log.h"

#include "Engine/Component.h"
#include "Engine/Scene.h"
#include "Utilitaries/DebugMemoryLeakCatcher.h"

Actor::Actor():
	mScene(Scene::ActiveScene),
	mState(ActorState::Active)
{
	DEBUGAddClass("Actor");
	mTransform2D = dynamic_cast<Transform2D*>(AddComponent(new Transform2D()));
	mTransform3D = dynamic_cast<Transform3D*>(AddComponent(new Transform3D(this, WORLD)));
}

Actor::~Actor() = default;

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
	mScene = nullptr;
	while (!mComponentList.empty())
	{
		mComponentList[0]->Destroy();
		delete mComponentList[0];
		mComponentList[0] = nullptr;
		mComponentList.erase(mComponentList.begin());
	}
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