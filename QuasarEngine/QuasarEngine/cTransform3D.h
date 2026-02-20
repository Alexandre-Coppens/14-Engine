#ifndef TRANSFORM3D_H
#define TRANSFORM3D_H

#include "Component.h"
#include "CommonLib.h"
#include "MathLib.h"

class Transform3D : public Component
{
protected:
	Vector3		mLocation{ Vector3Zero() };
	Quaternion	mRotation{ Quaternion() }; //Rechange this to a vector3
	Vector3		mScale   { Vector3One() };

	Matrix4Row mWorldTransform{ Matrix4Row::Mat4RowIdentity() };

	bool mNeedsUpdate{ true };

public:
	Vector3 getLocation()		const { return mLocation; }
	Quaternion getRotation()	const { return mRotation; }
	Vector3 getScale()			const { return mScale; }

	Matrix4Row getWorldTransform() const { return mWorldTransform; }

	void setLocation(const Vector3 _v)    { mLocation = _v; }
	void setRotation(const Quaternion _q) { mRotation = _q; }
	void setScale(const Vector3 _v)		  { mScale = _v; }

	void setLocationX(const float _f) { mLocation.x = _f; }
	void setLocationY(const float _f) { mLocation.y = _f; }
	void setLocationZ(const float _f) { mLocation.z = _f; }
	void setScaleX(const float _f) { mScale.x = _f; }
	void setScaleY(const float _f) { mScale.y = _f; }
	void setScaleZ(const float _f) { mScale.z = _f; }

	void addLocation(const Vector3 _v) { mLocation = Add(mLocation, _v); }
	void addLocationX(const float _f) { mLocation.x += _f; }
	void addLocationY(const float _f) { mLocation.y += _f; }
	void addLocationZ(const float _f) { mLocation.z += _f; }
	
	void combineRotation(const Quaternion _q) { mRotation *= _q; }
	void rotateAroundAxis(const Vector3 _axis, const float _angle) { mRotation *= QuatFromAxisAngle(_axis, _angle); }
	void rotateAroundX(const float _angle) { mRotation *= QuatFromAxisAngle(Vector3UnitX(), _angle); }
	void rotateAroundY(const float _angle) { mRotation *= QuatFromAxisAngle(Vector3UnitY(), _angle); }
	void rotateAroundZ(const float _angle) { mRotation *= QuatFromAxisAngle(Vector3UnitZ(), _angle); }

	void setTransform(Transform3D* _t3D) {
		mLocation = _t3D->mLocation;
		mRotation = _t3D->mRotation;
		mScale	  = _t3D->mScale;
	}

	Vector3 Forward()	const { return Transform(Vector3UnitX(), mRotation); }
	Vector3 Right()		const { return Transform(Vector3UnitY(), mRotation); }
	Vector3 Up()		const { return Transform(Vector3UnitZ(), mRotation); }

protected:
public:
	Transform3D();
	Transform3D(Actor* _pOwner, uint8_t _updateOrder);
	virtual ~Transform3D();
	Transform3D& operator= (Transform3D* _pTransform) { setTransform(_pTransform); }

	void OnStart()	override;
	void Update(float _deltaTime)	override;
	void OnEnd()	override;

	void ComputeWorldTransform();
};

#endif