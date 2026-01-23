#pragma once

#include "Component.h"
#include "Rectangle.h"
#include<vector>

class Actor;

enum class ColliderForm2D
{
	None,
	Box
};

class Collider : public Component
{
private:
	bool bIsColliding;
	std::vector<Actor*> vCollidingActors;

protected:
	static std::vector<Collider*> colliderList;
	ColliderForm2D eForm;

public:
	bool GetIsColliding() { return bIsColliding; }
	std::vector<Actor*> GetCollidingActors() { return vCollidingActors; }
	ColliderForm2D GetForm() { return eForm; }

private:
	bool BoxCollision(Rectangle c);

protected:
	virtual void CheckCollisions();

public:
	Collider(Actor* _pOwner, uint8_t _u8UpdateOrder);
	~Collider();

	void OnStart() override;
	void Update() override;
	void OnEnd() override;
};