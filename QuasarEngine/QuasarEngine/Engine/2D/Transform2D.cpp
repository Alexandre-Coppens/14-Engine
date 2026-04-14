#include "Transform2D.h"

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

void Transform2D::Update(float _deltaTime)
{
}

void Transform2D::Destroy()
{
	Component::Destroy();
}

void Transform2D::ComputeWorldTransform()
{
	
	if (!mNeedsUpdate) return;
	mWorldScale	   = Vector3One();
	mWorldRotation = Vector3Zero();
	mWorldLocation = Vector3Zero();
	
	mWorldScale    *= Vector3{getScale().x * getSize().x, getScale().y * getSize().y, 1.0f};
	mWorldRotation += Vector3{getRotation(), 0.0f, 0.0f };
	mWorldLocation += Vector3{getLocation().x, getLocation().y, 0.0f};

	mRotation = Fmod(mRotation, 360.0f);
	mWorldRotation.x = Fmod(mWorldRotation.x, 360.0f);
	computeRotations();

	mWorldTransform = Mat4RowCreateScale(mWorldScale);
	mWorldTransform *= Mat4RowCreateFromQuaternion(mWorldQRotation);
	mWorldTransform *= Mat4RowCreateTranslation(mWorldLocation);
	mNeedsUpdate = false;
}