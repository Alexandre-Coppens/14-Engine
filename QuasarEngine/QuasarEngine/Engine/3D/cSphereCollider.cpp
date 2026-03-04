#include "cSphereCollider.h"

#include "Engine/Actor.h"

SphereCollider::SphereCollider(Actor* _pOwner):
	Collider3D(_pOwner)
{
	mColliderType = SPHERE;
}
SphereCollider::~SphereCollider()
{
	Collider3D::~Collider3D();
}

//TODO: Make it affect scale
//Return a Vec4 that contains xyz = Location, w = radius
Vector4 SphereCollider::GetSphere()
{
	Vector3 pos = pOwner->getTransform3D()->getLocation();
	return Vector4(pos.x, pos.y, pos.z, mRadius);
}