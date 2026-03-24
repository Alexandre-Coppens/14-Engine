#pragma once
#include <vector>

#include "Engine/3D/cBoxCollider.h"
#include "Engine/Utilitaries/CommonLib.h"

class PhysicBody;

struct CollisionData
{
	bool isColliding		{ false };
	
	PhysicBody* bodyA		{nullptr};
	PhysicBody* bodyB		{nullptr};

	float friction			{ 0 };
    
	float penetration		{ 0 };
	Vector3 normal			{ Vector3Zero()};
	Vector3 collisionPoint	{ Vector3Zero()};
};

class Collider3D;
class CollisionManager
{
public:
	static CollisionData NO_COLLISION;
	static std::vector<Collider3D*> collidersList;
	
	static void AddCollider(Collider3D* _collider) {collidersList.push_back(_collider);}
	static void RemoveCollider(const Collider3D* _collider) {
		std::vector<Collider3D*>::iterator it;
		it = std::find(collidersList.begin(), collidersList.end(), _collider);
		if (it == collidersList.end()) return;
		collidersList.erase(it);
	}
	static std::vector<Collider3D*> getAllColliders() {return collidersList;}
	
	static void UpdatesCollisions();
	static void ResolveCollisions(std::vector<CollisionData> _collisionList);
	static CollisionData GetIsColliding(Collider3D* _colliderA, Collider3D* _colliderB);
	
	static CollisionData BoxToBox(Collider3D* _pBoxA, Collider3D* _pBoxB);
	static CollisionData BoxToSphere(Collider3D* _pBox, Collider3D* _pSphere);
	static CollisionData SphereToSphere(Collider3D* _pSphereA, Collider3D* _pSphereB);
	static float GetSeparatingPlane(Vector3 _diffPos, Vector3 _plane, BoxCollider* _boxA, BoxCollider* _boxB);
};
