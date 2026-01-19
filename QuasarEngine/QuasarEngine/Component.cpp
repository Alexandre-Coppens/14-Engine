#include "Component.h"
#include "Actor.h"

Component::Component(Actor* _pOwner, uint8_t _u8UpdateOrder):
	pOwner{_pOwner}, u8UpdateOrder{_u8UpdateOrder}
{
}

Component::~Component()
{
}

void Component::OnStart()
{
}

void Component::OnEnd()
{
}
