#pragma once
#include "Engine/3D/cCollider3D.h"

struct Vector4;
class Actor;
class SphereCollider : public Collider3D
{
private:
	float mRadius;
	
public:
	float getRadius() const {return mRadius;}
	
	void setRadius(const float _radius) {mRadius = _radius;}
	
public:
	SphereCollider(Actor* _pOwner);
	~SphereCollider() override;
	
	Vector4 GetSphere();
};
