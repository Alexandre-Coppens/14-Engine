#ifndef TRANSFORM3D_H
#define TRANSFORM3D_H

#include "Component.h"
#include "CommonLib.h"
#include "MathLib.h"

class Transform3D : public Component
{
protected:
	Vector3 mLocation{ Vector3Zero() };
	Vector3	mRotation{ Vector3Zero() };
	Vector3 mScale   { Vector3One() };

	Matrix4Row mWorldTransform{ Matrix4Row::Mat4RowIdentity() };

	bool mNeedsUpdate{ true };

public:
	Vector3 getLocation()	const { return mLocation; }
	Vector3 getRotation()	const { return mRotation; }
	Vector3 getScale()		const { return mScale; }

	Matrix4Row getWorldTransform() const { return mWorldTransform; }

	void setLocation(Vector3 _v) { mLocation = _v; }
	void setRotation(Vector3 _v) { mRotation = _v; }
	void setScale(Vector3 _v)	 { mScale = _v; }

	void setLocationX(float _f) { mLocation.x = _f; }
	void setLocationY(float _f) { mLocation.y = _f; }
	void setLocationZ(float _f) { mLocation.z = _f; }
	void setRotationX(float _f) { mRotation.x = _f; }
	void setRotationY(float _f) { mRotation.y = _f; }
	void setRotationZ(float _f) { mRotation.z = _f; }
	void setScaleX(float _f) { mScale.x = _f; }
	void setScaleY(float _f) { mScale.y = _f; }
	void setScaleZ(float _f) { mScale.z = _f; }

	void addLocation(Vector3 _v) { mLocation = Add(mLocation, _v); }
	void addLocationX(float _f) { mLocation.x += _f; }
	void addLocationY(float _f) { mLocation.y += _f; }
	void addLocationZ(float _f) { mLocation.z += _f; }
	void addRotationX(float _f) { mRotation.x += _f; }
	void addRotationY(float _f) { mRotation.y += _f; }
	void addRotationZ(float _f) { mRotation.z += _f; }

	void setTransform(Transform3D* _t3D) {
		mLocation = _t3D->mLocation;
		mRotation = _t3D->mRotation;
		mScale	  = _t3D->mScale;
	}

	//Vector3 Forward() const { return Transform(Vector3{1,0,0}, mRotation); }
	//Vector2 Right() const { return Vector2{ Cos(mRotation), -Sin(mRotation) }; }
	//Vector2 Up()	const { return Vector2{ Sin(mRotation), -Cos(mRotation) }; }

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