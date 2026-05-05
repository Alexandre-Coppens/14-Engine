#pragma once
#include "Engine/Actor.h"
#include "Engine/3D/cCollider3D.h"

class Mesh;
struct Vector4;
class Actor;
class SphereCollider : public Collider3D
{
private:
	float mRadius {1.0f};
	
public:
	float getRadius() const {return mRadius;}
	
	void setRadius(const float _radius) {mRadius = _radius;}
	
public:
	SphereCollider(Actor* _pOwner);
	~SphereCollider() override;
	
	Vector3 getCenter() override;
	
	Vector4 GetSphere();
};
