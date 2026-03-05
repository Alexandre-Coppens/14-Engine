#include "Component.h"
#include "Engine/Actor.h"

Component::Component(Actor* _pOwner, const uint8_t _updateOrder):
	pOwner{_pOwner}, mUpdateOrder{_updateOrder}
{
}

Component::~Component()
{
	OnEnd();
}

void Component::OnStart()
{
}

void Component::OnActorStart()
{
}

void Component::OnEnd()
{
	pOwner = nullptr;
}
