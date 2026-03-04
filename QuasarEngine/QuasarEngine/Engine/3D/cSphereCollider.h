#pragma once
#include "Engine/3D/cCollider3D.h"

class Mesh;
struct Vector4;
class Actor;
class SphereCollider : public Collider3D
{
private:
	float mRadius;
	Mesh* mDebugMesh;
	
public:
	float getRadius() const {return mRadius;}
	
	void setRadius(const float _radius) {mRadius = _radius;}
	
public:
	SphereCollider(Actor* _pOwner);
	~SphereCollider() override;
	
	void DrawDebug() override;
	
	Vector4 GetSphere();
};
