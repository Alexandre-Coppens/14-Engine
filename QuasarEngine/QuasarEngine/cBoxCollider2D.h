#pragma once

#include "cCollider.h"
#include "Rectangle.h"

class BoxCollider2D : public Collider
{
private:
	Rectangle collision;

public:
	Rectangle GetCollision() const { return collision; }

private:


public:
	BoxCollider2D(Actor* _pOwner, uint8_t _u8UpdateOrder, Rectangle _collision);
	~BoxCollider2D();

	void Update() override;
};