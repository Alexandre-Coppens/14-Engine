#pragma once
#include "Engine/Actor.h"
#include "Engine/3D/cCollider3D.h"

#include "Engine/Utilitaries/CommonLib.h"

class Mesh;
class Actor;
class BoxCollider : public Collider3D
{
private:
	
public:
	Vector3 getOffset() const {return mTransform->getLocation();}
	Vector3 getSize() const {return mTransform->getScale();}
	
	Vector3 getForward() const {return mTransform->Forward();}	//X Vector
	Vector3 getRight() const {return mTransform->Right();}		//Y Vector
	Vector3 getUp() const {return mTransform->Up();}		//Z Vector
	
	void setOffset(const Vector3 _offset)  {mTransform->setLocation(_offset);}
	void setSize(const Vector3 _size) {mTransform->setScale(_size);}
	
private:
public:
	BoxCollider(Actor* _pOwner);
	~BoxCollider() override;
	
	Vector3 getCenter() override;
	Vector3 getScale();
	std::vector<Vector3> getWorldVertices();
	
	void Destroy() override;
};
