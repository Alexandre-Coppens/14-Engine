#ifndef TRANSFORM3D_H
#define TRANSFORM3D_H

#include "Component.h"
#include "CommonLib.h"
#include "MathLib.h"

class Transform3D : public Component
{
protected:
	Vector3		mLocation { Vector3Zero() };
	Vector3		mRotation { Vector3Zero() }; 
	Quaternion	mQRotation{ Quaternion() }; 
	Vector3		mScale    { Vector3One() };

	Matrix4Row mWorldTransform{ Matrix4Row::Mat4RowIdentity() };

	bool mNeedsUpdate{ true };

public:
	Vector3 getLocation()	const { return mLocation; }
	Vector3 getRotation()	const { return mRotation; }
	Vector3 getScale()		const { return mScale; }

	Matrix4Row getWorldTransform() const { return mWorldTransform; }

	void setLocation(const Vector3 _v)  { mLocation = _v; }
	void setRotation(const Vector3 _v)  { mRotation = _v; }
	void setScale	(const Vector3 _v)	{ mScale = _v; }

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
	void addRotationX(const float _f) { mRotation.x += _f; }
	void addRotationY(const float _f) { mRotation.y += _f; }
	void addRotationZ(const float _f) { mRotation.z += _f; }
	
	void clampRotationY(const float _min, const float _max) {mRotation.y = Clamp(mRotation.y, _min, _max); }
	
	void combineRotation(const Quaternion _q) { mQRotation = Concatenate(mQRotation, _q);}
	void rotateAroundAxis(const Vector3 _axis, const float _angle) { combineRotation(QuatFromAxisAngle(_axis, ToRad(_angle))); }
	void rotateAroundX(const float _angle) { combineRotation(QuatFromAxisAngle(Forward(), ToRad(_angle))) ; }
	void rotateAroundY(const float _angle) { combineRotation(QuatFromAxisAngle(Right(), ToRad(_angle))); }
	void rotateAroundZ(const float _angle) { combineRotation(QuatFromAxisAngle(Up(), ToRad(_angle))); }

	void computeRotation(){
		mQRotation = Quaternion();
		rotateAroundZ(mRotation.z);
		rotateAroundY(mRotation.y);
		rotateAroundX(mRotation.x);
		ComputeWorldTransform();
	}
	
	void setTransform(const Transform3D* _t3D) {
		mLocation = _t3D->mLocation;
		mRotation = _t3D->mRotation;
		mScale	  = _t3D->mScale;
	}

	Vector3 Forward()	const { return Transform(Vector3UnitX(), mQRotation); }
	Vector3 Right()		const { return Transform(Vector3UnitY(), mQRotation); }
	Vector3 Up()		const { return Transform(Vector3UnitZ(), mQRotation); }

protected:
public:
	Transform3D();
	Transform3D(Actor* _pOwner, uint8_t _updateOrder);
	~Transform3D() override;
	Transform3D& operator= (const Transform3D* _pTransform) { setTransform(_pTransform); }

	void OnStart()	override;
	void Update(float _deltaTime)	override;
	void OnEnd()	override;

	void ComputeWorldTransform();
};

#endif