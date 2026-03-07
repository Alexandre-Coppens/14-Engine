#pragma once
#include "Engine/Actor.h"
#include "Engine/3D/cCollider3D.h"

#include "Engine/Utilitaries/CommonLib.h"

class Mesh;
class Actor;
class BoxCollider : public Collider3D
{
private:
	Vector3 mOffset;
	Vector3 mSize;
	
	Mesh* mDebugMesh;
	
public:
	Vector3 getOffset() const {return mOffset;}
	Vector3 getSize() const {return mSize;}
	
	void setOffset(const Vector3 _offset)  {mOffset = _offset;}
	void setSize(const Vector3 _v) {mSize = _v;}
	
private:
public:
	BoxCollider(Actor* _pOwner);
	~BoxCollider() override;
	
	Vector3 getCenter() override;

	
	void DrawDebug() override;
};
