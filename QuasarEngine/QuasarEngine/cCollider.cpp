#include "cCollider.h"
#include "cBoxCollider2D.h"
#include "Actor.h"
#include "Log.h"

std::vector<Collider*> Collider::colliderList;

Collider::Collider(Actor* _pOwner, uint8_t _u8UpdateOrder):
	Component(_pOwner, _u8UpdateOrder), eForm(ColliderForm2D::None)
{
    sName = "Collider";
}

Collider::~Collider()
{
}

void Collider::OnStart()
{
	colliderList.push_back(this);
}

void Collider::Update()
{
	CheckCollisions();
}

void Collider::OnEnd()
{
	colliderList.push_back(this);
}

void Collider::CheckCollisions()
{
    bIsColliding = false;
    vCollidingActors.empty();
    for (Collider* collider : colliderList)
    {
        if (collider == this) continue;
        switch (collider->GetForm())
        {
        case ColliderForm2D::None:
            break;

        case ColliderForm2D::Box:
            if (BoxCollision(static_cast<BoxCollider2D*>(collider)->GetCollision()))
            {
                Log::Info(GetOwner()->GetName() + " is colliding with: " + collider->GetOwner()->GetName());
                bIsColliding = true;
                vCollidingActors.push_back(collider->GetOwner());
            }
            break;
        }
    }
}

bool Collider::BoxCollision(Rectangle c)
{
    switch(eForm)
    {
    case ColliderForm2D::None:
        break;

    case ColliderForm2D::Box:
        Rectangle mc = static_cast<BoxCollider2D*>(this)->GetCollision();
        if (mc.position.x < c.position.x + c.dimensions.x &&
            c.position.x < mc.position.x + mc.dimensions.x &&
            mc.position.y < c.position.y + c.dimensions.y &&
            c.position.y < mc.position.y + mc.dimensions.y)
        {
            return true;
        }
        return false;
    }
}