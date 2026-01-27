#pragma once

#include "cCollider.h"
#include "Rectangle.h"

class BoxCollider2D : public Collider
{
private:
	Rectangle mCollision;

public:
	Rectangle GetCollision() const { return mCollision; }

private:
public:
	BoxCollider2D(Actor* _pOwner, uint8_t _updateOrder, Rectangle _collision);
	~BoxCollider2D();

	void Update() override;
};