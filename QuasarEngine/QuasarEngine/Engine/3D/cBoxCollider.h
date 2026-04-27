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
	Transform3D* getTransform() const {return mTransform;}
	
	Vector3 getForward() const {return mTransform->WorldForward();}	//X Vector
	Vector3 getRight() const {return mTransform->WorldRight();}		//Y Vector
	Vector3 getUp() const {return mTransform->WorldUp();}			//Z Vector
	
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
