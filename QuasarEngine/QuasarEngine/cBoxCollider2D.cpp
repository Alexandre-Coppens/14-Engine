#include "cBoxCollider2D.h"
#include "Actor.h"
#include "Log.h"

BoxCollider2D::BoxCollider2D(Actor* _pOwner, uint8_t _u8UpdateOrder, Rectangle _collision):
    Collider(_pOwner, _u8UpdateOrder), collision(_collision)
{
    eForm = ColliderForm2D::Box;
    sName = "BoxCollider2D";
}

BoxCollider2D::~BoxCollider2D()
{
}

void BoxCollider2D::Update()
{
    collision = Rectangle{ GetOwner()->GetTransform()->location, collision.dimensions };
    Collider::Update();
}
