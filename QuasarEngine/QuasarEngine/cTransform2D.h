#ifndef TRANSFORM2D_H
#define TRANSFORM2D_H

#include "Component.h"
#include "CommonLib.h"

class Transform2D : public Component
{
protected:
	Vector2 mLocation	{ Vector2Zero() };
	float	mRotation	{ 0.0f };
	Vector2 mSize		{ Vector2Zero() };
	Vector2 mScale		{ Vector2One() };

public:
	Vector2 getLocation()	const	{ return mLocation; }
	float   getRotation()	const	{ return mRotation; }
	Vector2 getSize()		const	{ return mSize; }
	Vector2 getScale()		const	{ return mScale; }

	void setLocation(Vector2 _v)	{ mLocation = _v; }
	void setRotation(float _f)		{ mRotation = _f; }
	void setSize(Vector2 _v)		{ mSize = _v; }
	void setScale(Vector2 _v)		{ mScale = _v; }

	void setLocationX(float _f)	{ mLocation.x = _f; }
	void setLocationY(float _f)	{ mLocation.y = _f; }
	void setSizeX(float _f)		{ mSize.x = _f; }
	void setSizeY(float _f)		{ mSize.y = _f; }
	void setScaleX(float _f)	{ mScale.x = _f; }
	void setScaleY(float _f)	{ mScale.y = _f; }

	void addLocationX(float _f) { mLocation.x += _f; }
	void addLocationY(float _f) { mLocation.y += _f; }
	void addRotation(float _f)  { mRotation += _f; }

	void setTransform(Transform2D* _t2D) {
		mLocation = _t2D->mLocation;
		mRotation = _t2D->mRotation;
		mSize	  = _t2D->mSize;
		mScale	  = _t2D->mScale;
	}

protected:
public:
	Transform2D();
	Transform2D(Actor* _pOwner, uint8_t _updateOrder);
	virtual ~Transform2D();
	Transform2D& operator= (Transform2D* _pTransform) { setTransform(_pTransform); }

	void OnStart()	override;
	void Update()	override;
	void OnEnd()	override;
};

#endif