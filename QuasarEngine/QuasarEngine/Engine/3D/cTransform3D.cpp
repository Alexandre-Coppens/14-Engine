#include "cTransform3D.h"
#include "Engine/Actor.h"

Transform3D::Transform3D() :
	Component(nullptr, 0) //Need to modify this
{
	mName = "Transform3D";
}

Transform3D::Transform3D(Actor* _pOwner, uint8_t _updateOrder) :
	Component(_pOwner, _updateOrder)
{
	mName = "Transform3D";
}

Transform3D::~Transform3D()
{
}

void Transform3D::OnStart()
{
}

void Transform3D::Update(float _deltaTime)
{
}

void Transform3D::OnEnd()
{
}

void Transform3D::ComputeWorldTransform()
{
	if (!mNeedsUpdate) return;
	mNeedsUpdate = false;
	mWorldTransform =  Mat4RowCreateScale(mScale);
	mWorldTransform *= Mat4RowCreateFromQuaternion(mQRotation);
	mWorldTransform *= Mat4RowCreateTranslation(mLocation);
}
