#ifndef TRANSFORM3D_H
#define TRANSFORM3D_H

#include "Engine/Component.h"
#include "Engine/Utilitaries/CommonLib.h"
#include "Engine/Utilitaries/MathLib.h"

enum Space
{
	WORLD,
	LOCAL
};

class Transform3D : public Component
{
protected:
	//Local and Set Accessible
	Vector3		mLocation { Vector3Zero() };
	Vector3		mRotation { Vector3Zero() }; 
	Quaternion	mQRotation{ Quaternion() }; 
	Vector3		mScale    { Vector3One() };

	//World and Get only accessible
	Vector3		mWorldLocation { Vector3Zero() };
	Vector3		mWorldRotation { Vector3Zero() }; 
	Quaternion	mWorldQRotation{ Quaternion() }; 
	Vector3		mWorldScale    { Vector3One() };

	mutable Matrix4Row mWorldTransform{ Matrix4Row::Mat4RowIdentity() };

	Space mSpace     {WORLD};
	bool mNeedsUpdate{ true };

public:
	Vector3 getLocation()		const { return mLocation; }
	Vector3 getRotation()		const { return mRotation; }
	Quaternion getQRotation()	const { return mQRotation; }
	Vector3 getScale()			const { return mScale; }

	Vector3 getWorldLocation()		const { return mWorldLocation; }
	Vector3 getWorldRotation()		const { return mWorldRotation; }
	Quaternion getWorldQRotation()	const { return mWorldQRotation; }
	Vector3 getWorldScale()			const { return mWorldScale; }

	Matrix4Row getWorldTransform() { ComputeWorldTransform(); return mWorldTransform; }

	void setNeedRecalculate() { mNeedsUpdate = true; }
	
	void setLocation(const Vector3 _v)  { mLocation = _v; mNeedsUpdate = true; }
	void setRotation(const Vector3 _v)  { mRotation = _v; mNeedsUpdate = true; }
	void setScale	(const Vector3 _v)	{ mScale = _v; mNeedsUpdate = true; }

	void setLocationX(const float _f) { mLocation.x = _f; mNeedsUpdate = true; }
	void setLocationY(const float _f) { mLocation.y = _f; mNeedsUpdate = true; }
	void setLocationZ(const float _f) { mLocation.z = _f; mNeedsUpdate = true; }
	void setScaleX(const float _f) { mScale.x = _f; mNeedsUpdate = true; }
	void setScaleY(const float _f) { mScale.y = _f; mNeedsUpdate = true; }
	void setScaleZ(const float _f) { mScale.z = _f; mNeedsUpdate = true; }

	void addLocation(const Vector3 _v) { mLocation = Add(mLocation, _v); mNeedsUpdate = true; }
	void addLocationX(const float _f) { mLocation.x += _f; mNeedsUpdate = true; }
	void addLocationY(const float _f) { mLocation.y += _f; mNeedsUpdate = true; }
	void addLocationZ(const float _f) { mLocation.z += _f; mNeedsUpdate = true; }
	void addRotation(const Vector3 _v) { mRotation = Add(mRotation, _v); mNeedsUpdate = true; }
	void addRotationX(const float _f) { mRotation.x += _f; mNeedsUpdate = true; }
	void addRotationY(const float _f) { mRotation.y += _f; mNeedsUpdate = true; }
	void addRotationZ(const float _f) { mRotation.z += _f; mNeedsUpdate = true; }
	
	void clampRotationY(const float _min, const float _max) {mRotation.y = Clamp(mRotation.y, _min, _max); mNeedsUpdate = true; }
	
	void combineRotation(const Quaternion _q) { mQRotation = Concatenate(mQRotation, _q);mNeedsUpdate = true; }
	void rotateAroundAxis(const Vector3 _axis, const float _angle) { combineRotation(QuatFromAxisAngle(_axis, ToRad(_angle))); mNeedsUpdate = true; }
	void rotateAroundX(const float _angle) { combineRotation(QuatFromAxisAngle(Forward(), ToRad(_angle))) ; mNeedsUpdate = true; }
	void rotateAroundY(const float _angle) { combineRotation(QuatFromAxisAngle(Right(), ToRad(_angle))); mNeedsUpdate = true; }
	void rotateAroundZ(const float _angle) { combineRotation(QuatFromAxisAngle(Up(), ToRad(_angle))); mNeedsUpdate = true; }

	void computeRotations(){
		mQRotation = Quaternion();
		rotateAroundZ(mRotation.z);
		rotateAroundY(mRotation.y);
		rotateAroundX(mRotation.x);

		mWorldQRotation = Quaternion();
		mWorldQRotation = Concatenate(mQRotation, QuatFromAxisAngle(Up(), ToRad(mWorldRotation.z)));
		mWorldQRotation = Concatenate(mQRotation, QuatFromAxisAngle(Right(), ToRad(mWorldRotation.y)));
		mWorldQRotation = Concatenate(mQRotation, QuatFromAxisAngle(Forward(), ToRad(mWorldRotation.x)));
	}
	
	void setTransform(const Transform3D* _t3D) {
		mLocation = _t3D->mLocation;
		mRotation = _t3D->mRotation;
		mScale	  = _t3D->mScale;
		mNeedsUpdate = true;
	}

	Vector3 Forward()	const { return Transform(Vector3UnitX(), mQRotation); }
	Vector3 Right()		const { return Transform(Vector3UnitY(), mQRotation); }
	Vector3 Up()		const { return Transform(Vector3UnitZ(), mQRotation); }

protected:
public:
	Transform3D(Actor* _pOwner, Space _space);
	~Transform3D() override;
	Transform3D& operator= (const Transform3D* _pTransform) { setTransform(_pTransform); return *this; }

	void OnStart()	override;
	void Update(float _deltaTime)	override;
	void Destroy()	override;

	void ComputeWorldTransform();
};

#endif