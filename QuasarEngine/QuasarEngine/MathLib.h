#ifndef MATHLIB_H
#define MATHLIB_H

#include "CommonLib.h"
#include "math.h"

//Vector 2

//Returns the Length of a Vector2
static inline float GetMagnitude(Vector2 v)
{
	return  sqrtf((v.x * v.x) + (v.y * v.y));
}
//Return a Normalized Vector2
static inline Vector2 Normalize(Vector2 v)
{
	Vector2 result = v;

	float length = sqrtf((v.x * v.x) + (v.y * v.y));
	if (length != 0.0f)
	{
		float nLength = 1.0f / length;
		result.x *= nLength;
		result.y *= nLength;
	}

	return result;
}
//Find the Dot between 2 Vector2
static inline float Dot(Vector2 v1, Vector2 v2)
{
	return  (v1.x * v2.x) + (v1.y * v2.y);
}

#endif // !MATHLIB_H