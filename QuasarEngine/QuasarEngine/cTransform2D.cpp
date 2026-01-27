#include "cTransform2D.h"

Transform2D::Transform2D():
	Component(nullptr, 0) //Need to modify this
{
}

Transform2D::Transform2D(Actor* _pOwner, uint8_t _updateOrder) :
	Component( _pOwner, _updateOrder)
{
	mName = "Transform2D";
}

Transform2D::~Transform2D()
{
}

void Transform2D::OnStart()
{
}

void Transform2D::Update()
{
}

void Transform2D::OnEnd()
{
}
