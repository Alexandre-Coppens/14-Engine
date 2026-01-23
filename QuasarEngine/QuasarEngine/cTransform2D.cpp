#include "cTransform2D.h"

Transform2D::Transform2D():
	Component(nullptr, 0) //Need to modify this
{
}

Transform2D::Transform2D(Actor* _pOwner, uint8_t _u8UpdateOrder) :
	Component( _pOwner, _u8UpdateOrder)
{
	sName = "Transform2D";
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
