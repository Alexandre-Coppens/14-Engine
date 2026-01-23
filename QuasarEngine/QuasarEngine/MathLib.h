#ifndef MATHLIB_H
#define MATHLIB_H

#pragma once

#include "CommonLib.h"
#include "math.h"
#include <limits>
#include <cmath>

const float PI = 3.1415926535f;
const float TWO_PI = PI * 2.0f;
const float PI_HALVED = PI / 2.0f;
const float INFINITY_POS = std::numeric_limits<float>::infinity();
const float INFINITY_NEG = -INFINITY_POS;

//Float / Int

inline float ToRad(float degrees) { return degrees * PI / 180.0f; }
inline float ToDeg(float radians) { return radians * 180.0f / PI; }

inline bool NearZero(float val, float epsilon = 0.001f) { return fabs(val) <= epsilon; }

template<typename T>
T Max(const T& a, const T& b) { return a < b ? b : a; }
template<typename T>
T Min(const T& a, const T& b) { return a < b ? a : b; }
template<typename T>
T Clamp(const T& val, const T& lower, const T& upper) { return Min(upper, Max(val, lower)); }
inline float Abs(float val) { return fabs(val); }
inline float Cos(float angle) { return cosf(angle); }
inline float Sin(float angle) { return sinf(angle); }
inline float Tan(float angle) { return tanf(angle); }
inline float ACos(float angle) { return acosf(angle); }
inline float ATan2(float opposite, float adjacent) { return atan2f(opposite, adjacent); }
inline float Cot(float angle) { return 1.0f / Tan(angle); }
inline float Lerp(float a, float b, float t) { return a + t * (b - a); }
inline float Sqrt(float val) { return sqrtf(val); }
inline float Fmod(float numer, float denom) { return std::fmod(numer, denom); }
inline int Round(float val) { return static_cast<int>(val); }

//Vector 2

//Returns the Length of a Vector2
inline float GetMagnitude(Vector2 v)
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
inline float Dot(Vector2 v1, Vector2 v2)
{
	return  (v1.x * v2.x) + (v1.y * v2.y);
}

#endif // !MATHLIB_H