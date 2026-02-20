#include "Component.h"
#include "Actor.h"

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

void Component::OnEnd()
{
	pOwner = nullptr;
}
