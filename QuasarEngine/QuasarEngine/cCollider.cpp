#include "cCollider.h"
#include "cBoxCollider2D.h"
#include "Actor.h"
#include "Log.h"

#include "cGravity2D.h"

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

void Collider::Update(float _deltaTime)
{
	CheckCollisions();
}

void Collider::OnEnd()
{
	mColliderList.push_back(this);
}

void Collider::SendToGravity()
{
    if (mIsColliding = false) return;
    Gravity2D* g = getOwner()->GetComponent<Gravity2D>();
    if (g == nullptr) return;
    g->Collided(currentDirection, currentOverlap);
}

void Collider::CheckCollisions()
{
    mIsColliding = false;
    mCollidingActors.clear();
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
                std::string dir;
                switch (currentDirection)
                {
                case Direction::UP:
                    dir = "Up";
                    break;
                case Direction::DOWN:
                    dir = "Down";
                    break;
                case Direction::LEFT:
                    dir = "Left";
                    break;
                case Direction::RIGHT:
                    dir = "Right";
                    break;
                case Direction::CENTER:
                    dir = "Center";
                    break;
                }

                mIsColliding = true;

                SendToGravity();
            }
            break;
        }
    }
    
}

bool Collider::BoxCollision(Rectangle c)
{
    float sizeX, sizeY, distX, distY;
    switch(mForm)
    {
    case ColliderForm2D::None:
        break;

    case ColliderForm2D::Box:
        Rectangle mc = static_cast<BoxCollider2D*>(this)->GetCollision();
        sizeX = (mc.size.x + c.size.x) * 0.5f;
        sizeY = (mc.size.y + c.size.y) * 0.5f;
        distX = mc.position.x - c.position.x;
        distY = mc.position.y - c.position.y;

        if (mc.position.x - mc.size.x * 0.5f < c.position.x  + c.size.x  * 0.5f &&
            c.position.x  - c.size.x  * 0.5f < mc.position.x + mc.size.x * 0.5f &&
            mc.position.y - mc.size.y * 0.5f < c.position.y  + c.size.y  * 0.5f &&
            c.position.y  - c.size.y  * 0.5f < mc.position.y + mc.size.y * 0.5f)
        {
            int left = 0, right = 0, up = 0, down = 0, best = 0;
            std::vector<Vector2> corners{
            mc.position + Vector2(-mc.size.x * 0.5f,  mc.size.y * 0.5f), //top left
            mc.position + Vector2(mc.size.x * 0.5f,  mc.size.y * 0.5f), //top right
            mc.position + Vector2(-mc.size.x * 0.5f, -mc.size.y * 0.5f),    //bot left
            mc.position + Vector2(mc.size.x * 0.5f, -mc.size.y * 0.5f) };   //bot right

            for (int i = 0; i < corners.size(); i++)
            {
                if (corners[i].x > c.position.x) left++;
                if (corners[i].x < c.position.x) right++;
                if (corners[i].y > c.position.y) up++;
                if (corners[i].y < c.position.y) down++;
            }

            best = Max(Max(left, right), Max(up, down));
            if (best == up) currentDirection = Direction::UP;
            else if (best == down) currentDirection = Direction::DOWN;
            else if (best == left) currentDirection = Direction::LEFT;
            else if (best == right) currentDirection = Direction::RIGHT;
            else currentDirection = Direction::CENTER;

            currentOverlap = Vector2((sizeX - abs(distX)) * distX > 0 ? 1 : -1, (sizeY - abs(distY)) * distY > 0 ? 1 : -1);

            return true;
        }
        return false;
    }
    return false;
}