#pragma once

#include "Engine/2D/cCollider.h"
#include "Engine/Utilitaries/Rectangle.h"

class BoxCollider2D : public Collider
{
private:
	Rectangle mCollision;

public:
	Rectangle GetCollision() const { return mCollision; }

private:
public:
	BoxCollider2D(Actor* _pOwner, uint8_t _updateOrder, CollisionPurpose _purpose, Rectangle _collision);

	void Update(float _deltaTime) override;
};