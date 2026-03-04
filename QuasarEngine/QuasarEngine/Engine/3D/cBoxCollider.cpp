#include "cBoxCollider.h"

BoxCollider::BoxCollider(Actor* _pOwner):
	Collider3D(_pOwner)
{
	mColliderType = BOX;
}
BoxCollider::~BoxCollider()
{
	Collider3D::~Collider3D();
}