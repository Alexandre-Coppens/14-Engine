#include "cBoxCollider2D.h"
#include "Actor.h"
#include "Log.h"

BoxCollider2D::BoxCollider2D(Actor* _pOwner, uint8_t _updateOrder, Rectangle _collision):
    Collider(_pOwner, _updateOrder), mCollision(_collision)
{
    mForm = ColliderForm2D::Box;
    mName = "BoxCollider2D";
}

BoxCollider2D::~BoxCollider2D()
{
}

void BoxCollider2D::Update(float _deltaTime)
{
    mCollision = Rectangle{ getOwner()->getTransform()->getLocation(), mCollision.size};
    Collider::Update(_deltaTime);
}
