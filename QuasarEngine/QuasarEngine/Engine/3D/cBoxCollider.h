#pragma once
#include "Engine/Actor.h"
#include "Engine/3D/cCollider3D.h"

#include "Engine/Utilitaries/CommonLib.h"

class Mesh;
class Actor;
class BoxCollider : public Collider3D
{
private:
	Vector3 mOffset {Vector3Zero()};
	Vector3 mSize   {Vector3One()};
	Transform3D* mpParentTransform {nullptr};
	
	Mesh* mDebugMesh {nullptr};
	
public:
	Vector3 getOffset() const {return mOffset;}
	Vector3 getSize() const {return mSize;}
	
	Vector3 getForward() const {return mpParentTransform->Forward();}	//X Vector
	Vector3 getRight() const {return mpParentTransform->Right();}		//Y Vector
	Vector3 getUp() const {return mpParentTransform->Up();}		//Z Vector
	
	void setOffset(const Vector3 _offset)  {mOffset = _offset;}
	void setSize(const Vector3 _v) {mSize = _v;}
	
private:
public:
	BoxCollider(Actor* _pOwner);
	~BoxCollider() override;
	
	Vector3 getCenter() override;
	std::vector<Vector3> getWorldVertices();
	
	void DrawDebug() override;
	
	void OnEnd() override;
};
