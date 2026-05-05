#pragma once

#include "Engine/Component.h"
#include "Engine/Utilitaries/Rectangle.h"
#include<vector>

class Actor;

enum class ColliderForm2D
{
	None,
	Box
};

enum class CollisionPurpose
{
	Block,
	Overlapp
};

enum class CollisionState
{
	None,
	Started,
	Continued
};

class Collider : public Component
{
private:
	bool mIsColliding;
	std::vector<Actor*> mCollidingActors;
	Direction currentDirection;
	Vector2 currentOverlap;

	CollisionState	 mCollisionState{ CollisionState::None };
	CollisionPurpose mCollisionPurpose;

protected:
	static std::vector<Collider*> mColliderList;
	ColliderForm2D mForm;

public:
	bool getIsColliding()					 const { return mIsColliding; }
	ColliderForm2D getForm()				 const { return mForm; }
	std::vector<Actor*> getCollidingActors() const { return mCollidingActors; }
	CollisionPurpose getCollisionPurpose()   const { return mCollisionPurpose; }
	bool getStartedCollision()	 const { return mCollisionState == CollisionState::Started; }
	bool getContinuedCollision() const { return mCollisionState == CollisionState::Continued; }

	void setCollisionPurpose(CollisionPurpose _purpose) { mCollisionPurpose = _purpose; }

private:
	bool BoxCollision(Rectangle _c);

protected:
	virtual void CheckCollisions();

public:
	Collider(Actor* _pOwner, uint8_t _updateOrder, CollisionPurpose _purpose);

	void OnStart() override;
	void Update(float _deltaTime) override;
	void Destroy() override;

	void SendToGravity();
};