#ifndef TRANSFORM2D_H
#define TRANSFORM2D_H

#include "Engine/Component.h"
#include "Engine/Utilitaries/MathLib.h"

class Transform2D : public Component
{
protected:
	Vector2 mLocation	   { Vector2Zero() };
	float	mRotation	   { 0.0f };
	Quaternion	mQRotation { Quaternion() }; 
	Vector2 mSize		   { Vector2Zero() };
	Vector2 mScale		   { Vector2One() };

	Vector3 mWorldLocation	    { Vector3One() };
	Vector3 mWorldRotation	    { Vector3One() };
	Quaternion	mWorldQRotation { Quaternion() }; 
	Vector3 mWorldScale	        { Vector3One() };

	mutable Matrix4Row mWorldTransform { Matrix4Row::Mat4RowIdentity() };
	
	bool mNeedsUpdate   {true};
	
public:
	Vector2 getLocation()	const	{ return mLocation; }
	float   getRotation()	const	{ return mRotation; }
	Vector2 getSize()		const	{ return mSize; }
	Vector2 getScale()		const	{ return mScale; }

	Matrix4Row getViewportTransform() { ComputeWorldTransform(); return mWorldTransform; }

	void setLocation(Vector2 _v)	{ mLocation = _v; mNeedsUpdate = true; }
	void setRotation(float _f)		{ mRotation = _f; mNeedsUpdate = true; }
	void setSize(Vector2 _v)		{ mSize = _v; mNeedsUpdate = true; }
	void setScale(Vector2 _v)		{ mScale = _v; mNeedsUpdate = true; }

	void setLocationX(float _f)	{ mLocation.x = _f; mNeedsUpdate = true; }
	void setLocationY(float _f)	{ mLocation.y = _f; mNeedsUpdate = true; }
	void setSizeX(float _f)		{ mSize.x = _f; mNeedsUpdate = true; }
	void setSizeY(float _f)		{ mSize.y = _f; mNeedsUpdate = true; }
	void setScaleX(float _f)	{ mScale.x = _f; mNeedsUpdate = true; }
	void setScaleY(float _f)	{ mScale.y = _f; mNeedsUpdate = true; }

	void addLocation(Vector2 _v) { mLocation = Add(mLocation, _v); mNeedsUpdate = true; }
	void addLocationX(float _f)  { mLocation.x += _f; mNeedsUpdate = true; }
	void addLocationY(float _f)  { mLocation.y += _f; mNeedsUpdate = true; }
	void addRotation(float _f)   { mRotation += _f; mNeedsUpdate = true; }

	void combineRotation(const Quaternion _q) { mQRotation = Concatenate(mQRotation, _q);mNeedsUpdate = true; }
	void rotateAroundZ(const float _angle) { combineRotation(QuatFromAxisAngle(Forward(), ToRad(_angle))) ; mNeedsUpdate = true; }
	
	void computeRotations(){
		mQRotation = Quaternion();
		rotateAroundZ(mRotation);

		mWorldQRotation = Quaternion();
		mWorldQRotation = Concatenate(mQRotation, QuatFromAxisAngle(Forward(), ToRad(mWorldRotation.z)));
	}
	
	void setTransform(Transform2D* _t2D) {
		mLocation = _t2D->mLocation;
		mRotation = _t2D->mRotation;
		mSize	  = _t2D->mSize;
		mScale	  = _t2D->mScale;
	}

	Vector2 Right() const { return Vector2{ Cos(mRotation), -Sin(mRotation) }; }
	Vector2 Up()	const { return Vector2{ Sin(mRotation), -Cos(mRotation) }; }

	Vector3 Forward()	const { return Transform(Vector3UnitZ(), mQRotation); }

protected:
public:
	Transform2D();
	Transform2D(Actor* _pOwner, uint8_t _updateOrder);
	virtual ~Transform2D();
	Transform2D& operator= (Transform2D* _pTransform) { setTransform(_pTransform); }

	void OnStart()	override;
	void Update(float _deltaTime)	override;
	void Destroy()	override;
	void ComputeWorldTransform();
};

#endif