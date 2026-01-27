#ifndef TRANSFORM2D_H
#define TRANSFORM2D_H

#include "Component.h"
#include "CommonLib.h"

class Transform2D : public Component
{
protected:
	

public:
	Vector2 location	{ Vector2Zero() };
	float rotation		{ 0.0f };
	Vector2 scale		{ Vector2One()  };

	Vector2 GetLocation()	const	{ return location; }
	float GetRotation()		const	{ return rotation; }
	Vector2 GetScale()		const	{ return scale; }

	void SetLocation(Vector2 _v)	{ location = _v; }
	void SetRotation(float _f)		{ rotation = _f; }
	void SetScale(Vector2 _v)		{ scale = _v; }

	void SetTransform(Transform2D* _t2D) {
		location	= _t2D->location;
		rotation	= _t2D->rotation;
		scale		= _t2D->scale;
	}

protected:
public:
	Transform2D();
	Transform2D(Actor* _pOwner, uint8_t _u8UpdateOrder);
	virtual ~Transform2D();
	Transform2D& operator= (Transform2D* _t2D) { SetTransform(_t2D); }

	void OnStart()	override;
	void Update()	override;
	void OnEnd()	override;
};

#endif