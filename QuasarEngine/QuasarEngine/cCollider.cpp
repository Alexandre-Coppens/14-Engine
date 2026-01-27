#include "cCollider.h"
#include "cBoxCollider2D.h"
#include "Actor.h"
#include "Log.h"

std::vector<Collider*> Collider::mColliderList;

Collider::Collider(Actor* _pOwner, uint8_t _u8UpdateOrder):
	Component(_pOwner, _u8UpdateOrder), mForm(ColliderForm2D::None)
{
    mName = "Collider";
}

Collider::~Collider()
{
}

void Collider::OnStart()
{
	mColliderList.push_back(this);
}

void Collider::Update()
{
	CheckCollisions();
}

void Collider::OnEnd()
{
	mColliderList.push_back(this);
}

void Collider::CheckCollisions()
{
    mIsColliding = false;
    mCollidingActors.empty();
    for (Collider* collider : mColliderList)
    {
        if (collider == this) continue;
        switch (collider->getForm())
        {
        case ColliderForm2D::None:
            break;

        case ColliderForm2D::Box:
            if (BoxCollision(static_cast<BoxCollider2D*>(collider)->GetCollision()))
            {
                Log::Info(getOwner()->getName() + " is colliding with: " + collider->getOwner()->getName());
                mIsColliding = true;
                mCollidingActors.push_back(collider->getOwner());
            }
            break;
        }
    }
}

bool Collider::BoxCollision(Rectangle c)
{
    switch(mForm)
    {
    case ColliderForm2D::None:
        break;

    case ColliderForm2D::Box:
        Rectangle mc = static_cast<BoxCollider2D*>(this)->GetCollision();
        if (mc.position.x < c.position.x + c.size.x &&
            c.position.x < mc.position.x + mc.size.x &&
            mc.position.y < c.position.y + c.size.y &&
            c.position.y < mc.position.y + mc.size.y)
        {
            return true;
        }
        return false;
    }
}