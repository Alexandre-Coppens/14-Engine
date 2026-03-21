#include "Component.h"
#include "Engine/Actor.h"
#include "Utilitaries/DebugMemoryLeakCatcher.h"

Component::Component(Actor* _pOwner, const uint8_t _updateOrder):
	pOwner{_pOwner}, mUpdateOrder{_updateOrder}
{
	DEBUGAddClass("Component");
}

Component::~Component() = default;

void Component::OnStart()
{
}

void Component::OnActorStart()
{
}

void Component::Destroy()
{
	delete mTransform;
	mTransform = nullptr;
	
	pOwner = nullptr;
	DEBUGRemoveClass("Component");
}

void Component::RecalculateTransform()
{
	if (mTransform != nullptr)
	{
		mTransform->setNeedRecalculate();
		mTransform->ComputeWorldTransform();
	}
}
