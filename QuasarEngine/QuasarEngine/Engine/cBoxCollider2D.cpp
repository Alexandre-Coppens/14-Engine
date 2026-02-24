#include "cBoxCollider2D.h"
#include "Engine/Actor.h"

BoxCollider2D::BoxCollider2D(Actor* _pOwner, uint8_t _updateOrder, CollisionPurpose _purpose, Rectangle _collision):
    Collider(_pOwner, _updateOrder, _purpose), mCollision(_collision)
{
    mForm = ColliderForm2D::Box;
    mName = "BoxCollider2D";
}

void BoxCollider2D::Update(float _deltaTime)
{
    mCollision = Rectangle{ getOwner()->getTransform2D()->getLocation(), mCollision.size};
    Collider::Update(_deltaTime);
}