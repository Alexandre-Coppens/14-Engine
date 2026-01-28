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
	bool mIsColliding;
	std::vector<Actor*> mCollidingActors;

protected:
	static std::vector<Collider*> mColliderList;
	ColliderForm2D mForm;

public:
	bool getIsColliding()					 const { return mIsColliding; }
	ColliderForm2D getForm()				 const { return mForm; }
	std::vector<Actor*> getCollidingActors() const { return mCollidingActors; }

private:
	bool BoxCollision(Rectangle _c);

protected:
	virtual void CheckCollisions();

public:
	Collider(Actor* _pOwner, uint8_t _updateOrder);
	~Collider();

	void OnStart() override;
	void Update() override;
	void OnEnd() override;

	void SendToGravity();
};