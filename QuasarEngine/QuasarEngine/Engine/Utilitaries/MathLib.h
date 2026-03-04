#ifndef MATHLIB_H
#define MATHLIB_H

#pragma once

#include "Engine/Utilitaries/CommonLib.h"
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
inline float Pow(float x) { return x * x; }
inline float Lerp(float a, float b, float t) { return a + t * (b - a); }
inline float Sqrt(float val) { return sqrtf(val); }
inline float Fmod(float numer, float denom) { return std::fmod(numer, denom); }
inline int Round(float val) { return static_cast<int>(val); }

//Vector 2
static const Vector2 Vector2Infinity() { return Vector2{ INFINITY_POS, INFINITY_POS }; }
static const Vector2 Vector2NegInfinity() { return Vector2{ INFINITY_NEG, INFINITY_NEG }; }


//Returns the Length of a Vector2
inline float GetMagnitude(Vector2 v)
{
	return  sqrtf((v.x * v.x) + (v.y * v.y));
}
//Return a Normalized Vector2
static inline Vector2 Normalize(Vector2 v)
{
	Vector2 result = v;

	float len = sqrtf((v.x * v.x) + (v.y * v.y));
	float nLen = 1.0f / len;
	result.x *= nLen;
	result.y *= nLen;

	return result;
}
//Find the Dot between 2 Vector2
inline float Dot(Vector2 v1, Vector2 v2)
{
	return  (v1.x * v2.x) + (v1.y * v2.y);
}

inline bool LineDetection(Vector2 v1, Vector2 v2)
{
	return false;
}

//Vector 3

static const Vector3 Vector3Infinity() { return Vector3{ INFINITY_POS, INFINITY_POS, INFINITY_POS }; }
static const Vector3 Vector3NegInfinity() { return Vector3{ INFINITY_NEG, INFINITY_NEG, INFINITY_NEG }; }

inline const float* GetAsFloatPtr(Vector3 v)
{
	return reinterpret_cast<const float*>(&v.x);
}

static inline float LengthSq(Vector3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

static inline float Length(Vector3 v)
{
	return (Sqrt(LengthSq(v)));
}

// Normalize the provided vector
static inline Vector3 Normalize(const Vector3 v)
{
	Vector3 result = v;
	float len = Length(v);
	float nLen = 1.0f / len;
	result.x *= nLen;
	result.y *= nLen;
	result.z *= nLen;
	return result;
}

// Dot product between two vectors (a dot b)
static inline float Dot(const Vector3& a, const Vector3& b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// Cross product between two vectors (a cross b)
static inline Vector3 Cross(const Vector3& a, const Vector3& b)
{
	Vector3 temp = Vector3Zero();
	temp.x = a.y * b.z - a.z * b.y;
	temp.y = a.z * b.x - a.x * b.z;
	temp.z = a.x * b.y - a.y * b.x;
	return temp;
}

// Lerp from A to B by f
static inline Vector3 Lerp(const Vector3& a, const Vector3& b, float f)
{
	return Vector3(a + ((b - a) * f));
}

// Reflect V about (normalized) N
static inline Vector3 Reflect(const Vector3& v, const Vector3& n)
{
	return v - 2.0f * n * Dot(v, n) ;
}

static inline Vector3 Transform(Vector3& vec, Matrix4& mat, float w = 1.0f)
{
	Vector3 retVal = Vector3Zero();
	retVal.x = vec.x * mat(0, 0) + vec.y * mat(1, 0) +
		vec.z * mat(2, 0) + w * mat(3, 0);
	retVal.y = vec.x * mat(0, 1) + vec.y * mat(1, 1) +
		vec.z * mat(2, 1) + w * mat(3, 1);
	retVal.z = vec.x * mat(0, 2) + vec.y * mat(1, 2) +
		vec.z * mat(2, 2) + w * mat(3, 2);
	//ignore w since we aren't returning a new value for it...
	return retVal;
}

// This will transform the vector and renormalize the w component
static inline Vector3 TransformWithPerspDiv(Vector3& vec, Matrix4& mat, float w = 1.0f)
{
	Vector3 retVal = Vector3Zero();
	retVal.x = vec.x * mat(0, 0) + vec.y * mat(1, 0) +
		vec.z * mat(2, 0) + w * mat(3, 0);
	retVal.y = vec.x * mat(0, 1) + vec.y * mat(1, 1) +
		vec.z * mat(2, 1) + w * mat(3, 1);
	retVal.z = vec.x * mat(0, 2) + vec.y * mat(1, 2) +
		vec.z * mat(2, 2) + w * mat(3, 2);
	float transformedW = vec.x * mat(0, 3) + vec.y * mat(1, 3) +
		vec.z * mat(2, 3) + w * mat(3, 3);
	if (!NearZero(Abs(transformedW)))
	{
		transformedW = 1.0f / transformedW;
		retVal *= transformedW;
	}
	return retVal;
}

// Transform a Vector3 by a quaternion
static inline Vector3 Transform(const Vector3& v, const Quaternion& q)
{
	// v + 2.0*cross(q.xyz, cross(q.xyz,v) + q.w*v);
	Vector3 qv(q.x, q.y, q.z);
	Vector3 retVal = v;
	retVal += 2.0f * Cross(qv, Cross(qv, v) + q.w * v);
	return retVal;
}

//Vector 4

static inline float LengthSqr(const Vector4& v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

static inline float Length(const Vector4& v)
{
	return Sqrt(LengthSqr(v));
}

// Cast to a const float pointer
inline const float* GetAsFloatPtr(Vector4 v)
{
	return reinterpret_cast<const float*>(&v.x);
}

//float& operator[](const Vector4& v, int i)
//{
//	return *(reinterpret_cast<float*>(&v.x) + i);
//}

// Normalize the provided vector
static inline Vector4 Normalize(const Vector4& v)
{
	Vector4 result = v;
	float len = Length(v);
	float nLen = 1.0f / len;
	result.x *= nLen;
	result.y *= nLen;
	result.z *= nLen;
	result.w *= nLen;
	return result;
}

// Dot product between two vectors (a dot b)
static inline float Dot(const Vector4& a, const Vector4& b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// Cross product between two vectors (a cross b)
static inline Vector4 Cross(const Vector4& a, const Vector4& b)
{
	Vector4 temp;
	temp.x = a.y * b.z - a.z * b.y;
	temp.y = a.z * b.x - a.x * b.z;
	temp.z = a.x * b.y - a.y * b.x;
	return temp;
}

// Lerp from A to B by f
static inline Vector4 Lerp(const Vector4& a, const Vector4& b, float f)
{
	return Vector4(a + f * (b - a));
}

// Reflect V about (normalized) N
static inline Vector4 Reflect(const Vector4& v, const Vector4& n)
{
	return v - 2.0f * Dot(v, n) * n;
}

//Quaternion

static inline Quaternion QuatFromAxisAngle(const Vector3& axis, float angle) {
	Quaternion result = Quaternion::QuatIdentity();
	float scalar = Sin(angle / 2.0f);
	result.x = axis.x * scalar;
	result.y = axis.y * scalar;
	result.z = axis.z * scalar;
	result.w = Cos(angle / 2.0f);
	return result;
}

static inline Quaternion Conjugate(Quaternion& q)
{
	q.x *= -1.0f;
	q.y *= -1.0f;
	q.z *= -1.0f;
	return q;
}

static inline float LengthSqr(const Quaternion& q)
{
	return (q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

static inline float Length(const Quaternion& q)
{
	return Sqrt(LengthSqr(q));
}

static inline Quaternion Normalize(Quaternion& q)
{
	Quaternion result = q;
	float len = Length(q);
	float nLen = 1.0f / len;
	result.x *= nLen;
	result.y *= nLen;
	result.z *= nLen;
	result.w *= nLen;
	return result;
}

// Linear interpolation
static inline Quaternion Lerp(const Quaternion& a, const Quaternion& b, float f)
{
	Quaternion retVal;
	retVal.x = Lerp(a.x, b.x, f);
	retVal.y = Lerp(a.y, b.y, f);
	retVal.z = Lerp(a.z, b.z, f);
	retVal.w = Lerp(a.w, b.w, f);
	retVal = Normalize(retVal);
	return retVal;
}

static inline float Dot(const Quaternion& a, const Quaternion& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

// Spherical Linear Interpolation
static inline Quaternion Slerp(const Quaternion& a, const Quaternion& b, float f)
{
	float rawCosm = Dot(a, b);

	float cosom = -rawCosm;
	if (rawCosm >= 0.0f)
	{
		cosom = rawCosm;
	}

	float scale0, scale1;

	if (cosom < 0.9999f)
	{
		const float omega = ACos(cosom);
		const float invSin = 1.f / Sin(omega);
		scale0 = Sin((1.f - f) * omega) * invSin;
		scale1 = Sin(f * omega) * invSin;
	}
	else
	{
		// Use linear interpolation if the quaternions
		// are collinear
		scale0 = 1.0f - f;
		scale1 = f;
	}

	if (rawCosm < 0.0f)
	{
		scale1 = -scale1;
	}

	Quaternion retVal;
	retVal.x = scale0 * a.x + scale1 * b.x;
	retVal.y = scale0 * a.y + scale1 * b.y;
	retVal.z = scale0 * a.z + scale1 * b.z;
	retVal.w = scale0 * a.w + scale1 * b.w;
	retVal = Normalize(retVal);
	return retVal;
}

// Concatenate
// Rotate by q FOLLOWED BY p
static inline Quaternion Concatenate(const Quaternion& q, const Quaternion& p)
{
	Quaternion retVal;

	// Vector component is:
	// ps * qv + qs * pv + pv x qv
	Vector3 qv(q.x, q.y, q.z);
	Vector3 pv(p.x, p.y, p.z);
	Vector3 newVec = p.w * qv + q.w * pv + Cross(pv, qv);
	retVal.x = newVec.x;
	retVal.y = newVec.y;
	retVal.z = newVec.z;

	// Scalar component is:
	// ps * qs - pv . qv
	retVal.w = p.w * q.w - Dot(pv, qv);

	return retVal;
}

static inline Matrix4 AsMatrix(const Quaternion& q) 
{
	// Transposed?

	const float xx = q.x * q.x;
	const float yy = q.y * q.y;
	const float zz = q.z * q.z;
	const float ww = q.w * q.w;
	const float xy = q.x * q.y;
	const float xz = q.x * q.z;
	const float xw = q.x * q.w;
	const float yz = q.y * q.z;
	const float yw = q.y * q.w;
	const float zw = q.z * q.w;


	array<float, 16> temp;

	temp[0] = 1.0f - 2.0f * (yy + zz);
	temp[1] = 2.0f * (xy - zw);
	temp[2] = 2.0f * (xz + yw);
	temp[3] = 0.0f;

	temp[4] = 2.0f * (xy + zw);
	temp[5] = 1.0f - 2.0f * (xx + zz);
	temp[6] = 2.0f * (yz - xw);
	temp[7] = 0.0f;

	temp[8] = 2.0f * (xz - yw);
	temp[9] = 2.0f * (yz + xw);
	temp[10] = 1.0f - 2.0f * (xx + yy);
	temp[11] = 0.0f;

	temp[12] = 0.0f;
	temp[13] = 0.0f;
	temp[14] = 0.0f;
	temp[15] = 1.0f;

	Matrix4 m = Matrix4(temp);
	return m;
}

static inline Matrix4Row AsMatrixRow(const Quaternion& q) 
{
	Matrix4Row m;

	const float xx = q.x * q.x;
	const float yy = q.y * q.y;
	const float zz = q.z * q.z;
	const float ww = q.w * q.w;
	const float xy = q.x * q.y;
	const float xz = q.x * q.z;
	const float xw = q.x * q.w;
	const float yz = q.y * q.z;
	const float yw = q.y * q.w;
	const float zw = q.z * q.w;

	m.mat[0][0] = 1.0f - 2.0f * (yy + zz);
	m.mat[0][1] = 2.0f * (xy - zw);
	m.mat[0][2] = 2.0f * (xz + yw);
	m.mat[0][3] = 0.0f;

	m.mat[1][0] = 2.0f * (xy + zw);
	m.mat[1][1] = 1.0f - 2.0f * (xx + zz);
	m.mat[1][2] = 2.0f * (yz - xw);
	m.mat[1][3] = 0.0f;

	m.mat[2][0] = 2.0f * (xz - yw);
	m.mat[2][1] = 2.0f * (yz + xw);
	m.mat[2][2] = 1.0f - 2.0f * (xx + yy);
	m.mat[2][3] = 0.0f;

	m.mat[3][0] = 0.0f;
	m.mat[3][1] = 0.0f;
	m.mat[3][2] = 0.0f;
	m.mat[3][3] = 1.0f;

	return m;
}

//Matrix4

static inline const float* GetAsFloatPtr(Matrix4 m4)
{
	return reinterpret_cast<const float*>(&m4.mat[0]);
}

// Invert the matrix - super slow
static inline Matrix4 Invert(Matrix4& m)
{
	float tmp[12];
	float src[16];
	float dst[16];
	float det;

	// Transpose matrix
	// row 1 to col 1
	src[0] = m.mat[0];
	src[4] = m.mat[1];
	src[8] = m.mat[2];
	src[12] = m.mat[3];

	// row 2 to col 2
	src[1] = m.mat[4];
	src[5] = m.mat[5];
	src[9] = m.mat[6];
	src[13] = m.mat[7];

	// row 3 to col 3
	src[2] = m.mat[8];
	src[6] = m.mat[9];
	src[10] = m.mat[10];
	src[14] = m.mat[11];

	// row 4 to col 4
	src[3] = m.mat[12];
	src[7] = m.mat[13];
	src[11] = m.mat[14];
	src[15] = m.mat[15];

	// Calculate cofactors
	tmp[0] = src[10] * src[15];
	tmp[1] = src[11] * src[14];
	tmp[2] = src[9] * src[15];
	tmp[3] = src[11] * src[13];
	tmp[4] = src[9] * src[14];
	tmp[5] = src[10] * src[13];
	tmp[6] = src[8] * src[15];
	tmp[7] = src[11] * src[12];
	tmp[8] = src[8] * src[14];
	tmp[9] = src[10] * src[12];
	tmp[10] = src[8] * src[13];
	tmp[11] = src[9] * src[12];

	dst[0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
	dst[0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
	dst[1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
	dst[1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
	dst[2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
	dst[2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
	dst[3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
	dst[3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
	dst[4] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
	dst[4] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
	dst[5] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
	dst[5] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
	dst[6] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
	dst[6] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
	dst[7] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
	dst[7] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];

	tmp[0] = src[2] * src[7];
	tmp[1] = src[3] * src[6];
	tmp[2] = src[1] * src[7];
	tmp[3] = src[3] * src[5];
	tmp[4] = src[1] * src[6];
	tmp[5] = src[2] * src[5];
	tmp[6] = src[0] * src[7];
	tmp[7] = src[3] * src[4];
	tmp[8] = src[0] * src[6];
	tmp[9] = src[2] * src[4];
	tmp[10] = src[0] * src[5];
	tmp[11] = src[1] * src[4];

	dst[8] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
	dst[8] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
	dst[9] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
	dst[9] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
	dst[10] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
	dst[10] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
	dst[11] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
	dst[11] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
	dst[12] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
	dst[12] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
	dst[13] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
	dst[13] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
	dst[14] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
	dst[14] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
	dst[15] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
	dst[15] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];

	// Calculate determinant
	det = src[0] * dst[0] + src[1] * dst[1] + src[2] * dst[2] + src[3] * dst[3];

	// Inverse of matrix is divided by determinant
	det = 1 / det;
	for (int j = 0; j < 16; j++)
	{
		dst[j] *= det;
	}

	// Set it back
	int k = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m.mat[k] = dst[i * 4 + j];
			++k;
		}
	}
	return m;
}

static inline Vector3 GetTranslation(const Matrix4& m)
{

	return Vector3(m.mat[12], m.mat[13], m.mat[14]);
}

static inline Vector3 GetXAxis(const Matrix4& m) 
{
	return Normalize(Vector3(m.mat[0], m.mat[1], m.mat[2]));
}

static inline Vector3 GetYAxis(const Matrix4& m) 
{
	return Normalize(Vector3(m.mat[4], m.mat[5], m.mat[6]));
}

static inline Vector3 GetZAxis(const Matrix4& m) 
{
	return Normalize(Vector3(m.mat[8], m.mat[9], m.mat[10]));
}

static inline Vector3 GetScale(const Matrix4& m) 
{
	Vector3 retVal = Vector3Zero();
	retVal.x = Length(Vector3(m.mat[0], m.mat[1], m.mat[2]));
	retVal.y = Length(Vector3(m.mat[4], m.mat[5], m.mat[6]));
	retVal.z = Length(Vector3(m.mat[8], m.mat[9], m.mat[10]));
	return retVal;
}

static inline  Matrix4 CreateScale(float xScale, float yScale, float zScale)
{
	array<float, 16> temp =
	{
		xScale, 0.0f, 0.0f, 0.0f,
		0.0f, yScale, 0.0f, 0.0f,
		0.0f, 0.0f, zScale, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	return Matrix4(temp);
}

static inline  Matrix4 Mat4CreateScale(const Vector3& scaleVector)
{
	return CreateScale(scaleVector.x, scaleVector.y, scaleVector.z);
}

static inline  Matrix4 Mat4CreateScale(float scale)
{
	return CreateScale(scale, scale, scale);
}

static inline  Matrix4 Mat4CreateRotationX(float theta)
{
	array<float, 16> temp =
	{
		1.0f, 0.0f, 0.0f , 0.0f,
		0.0f, Cos(theta), -Sin(theta), 0.0f,
		0.0f, Sin(theta), Cos(theta), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};
	return Matrix4(temp);
}

static inline  Matrix4 Mat4CreateRotationY(float theta)
{
	array<float, 16> temp =
	{
		Cos(theta), 0.0f, Sin(theta), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-Sin(theta), 0.0f, Cos(theta), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};
	return Matrix4(temp);
}

static inline  Matrix4 Mat4CreateRotationZ(float theta)
{
	array<float, 16> temp =
	{
		Cos(theta), -Sin(theta), 0.0f, 0.0f,
		Sin(theta), Cos(theta), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};
	return Matrix4(temp);
}

static inline  Matrix4 Mat4CreateTranslation(const Vector3& trans)
{
	array<float, 16> temp =
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		trans.x, trans.y, trans.z, 1.0f
	};
	return Matrix4(temp);
}

static inline  Matrix4 Mat4CreateSimpleViewProj(float width, float height)
{
	array<float, 16> temp =
	{
		2.0f / width, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / height, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	return Matrix4(temp);
}

static inline  Matrix4 Mat4CreateFromQuaternion(const Quaternion& q)
{
	array<float, 16> temp;
	temp[0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
	temp[1] = 2.0f * q.x * q.y - 2.0f * q.w * q.z;
	temp[2] = 2.0f * q.x * q.z + 2.0f * q.w * q.y;
	temp[3] = 0.0f;

	temp[4] = 2.0f * q.x * q.y + 2.0f * q.w * q.z;
	temp[5] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
	temp[6] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
	temp[7] = 0.0f;

	temp[8] = 2.0f * q.x * q.z - 2.0f * q.w * q.y;
	temp[9] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
	temp[10] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;
	temp[11] = 0.0f;

	temp[12] = 0.0f;
	temp[13] = 0.0f;
	temp[14] = 0.0f;
	temp[15] = 1.0f;

	return Matrix4(temp);
}

static inline  Matrix4 Mat4CreateLookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
{
	Vector3 zaxis = Normalize(eye - target);
	Vector3 normalizedUp = Normalize(up);
	Vector3 xaxis = Normalize(Cross(normalizedUp, zaxis));
	Vector3 yaxis = Normalize(Cross(zaxis, xaxis));

	array<float, 16> temp =
	{
		xaxis.x, yaxis.x, zaxis.x, 0.0f,
		xaxis.y, yaxis.y, zaxis.y, 0.0f,
		xaxis.z, yaxis.z, zaxis.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	Matrix4 t = Matrix4(temp);
	Matrix4 translation = Mat4CreateTranslation(Vector3(-eye.x, -eye.y, -eye.z));
	return t * translation;
}

static inline  Matrix4 CreateOrtho(float width, float height, float near, float far)
{
	array<float, 16> temp =
	{
		2.0f / width, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / height, 0.0f, 0.0f,
		0.0f, 0.0f, 2.0f / (near - far), 0.0f,
		0.0f, 0.0f, (far + near) / (far - far), 1.0f
	};
	return Matrix4(temp);
}

static inline  Matrix4 CreatePerspectiveFOV(float fovY, float width, float height, float near, float far)
{
	float yScale = Cot(fovY / 2.0f);
	float xScale = yScale * height / width;
	array<float, 16> temp =
	{
		xScale, 0.0f, 0.0f, 0.0f,
		0.0f, yScale, 0.0f, 0.0f,
		0.0f, 0.0f, near + far / (near - far), -1.0f,
		0.0f, 0.0f,  2.0f * near * far / (near - far), 0.0f
	};
	return Matrix4(temp);
}

static inline  Matrix4 CreatePerspective(float left, float right, float bottom, float top, float near, float far)
{
	array<float, 16> temp =
	{
		2 * near / (right - left), 0.0f, 0.0f, 0.0f,
		0.0f, 2 * near / (top - bottom), 0.0f, 0.0f,
		(right + left) / (right - left), (top + bottom) / (top - bottom), (far + near) / (near - far), -1.0f,
		0.0f, 0.0f, 2 * near * far / (near - far), 0.0f
	};
	return Matrix4(temp);
}

//Matrix4Row

static inline void Invert(Matrix4Row m)
{
	float tmp[12];
	float src[16];
	float dst[16];
	float det;

	// Transpose matrix
	// row 1 to col 1
	src[0] = m.mat[0][0];
	src[4] = m.mat[0][1];
	src[8] = m.mat[0][2];
	src[12] = m.mat[0][3];

	// row 2 to col 2
	src[1] = m.mat[1][0];
	src[5] = m.mat[1][1];
	src[9] = m.mat[1][2];
	src[13] = m.mat[1][3];

	// row 3 to col 3
	src[2] = m.mat[2][0];
	src[6] = m.mat[2][1];
	src[10] = m.mat[2][2];
	src[14] = m.mat[2][3];

	// row 4 to col 4
	src[3] = m.mat[3][0];
	src[7] = m.mat[3][1];
	src[11] = m.mat[3][2];
	src[15] = m.mat[3][3];

	// Calculate cofactors
	tmp[0] = src[10] * src[15];
	tmp[1] = src[11] * src[14];
	tmp[2] = src[9] * src[15];
	tmp[3] = src[11] * src[13];
	tmp[4] = src[9] * src[14];
	tmp[5] = src[10] * src[13];
	tmp[6] = src[8] * src[15];
	tmp[7] = src[11] * src[12];
	tmp[8] = src[8] * src[14];
	tmp[9] = src[10] * src[12];
	tmp[10] = src[8] * src[13];
	tmp[11] = src[9] * src[12];

	dst[0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
	dst[0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
	dst[1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
	dst[1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
	dst[2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
	dst[2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
	dst[3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
	dst[3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
	dst[4] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
	dst[4] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
	dst[5] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
	dst[5] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
	dst[6] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
	dst[6] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
	dst[7] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
	dst[7] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];

	tmp[0] = src[2] * src[7];
	tmp[1] = src[3] * src[6];
	tmp[2] = src[1] * src[7];
	tmp[3] = src[3] * src[5];
	tmp[4] = src[1] * src[6];
	tmp[5] = src[2] * src[5];
	tmp[6] = src[0] * src[7];
	tmp[7] = src[3] * src[4];
	tmp[8] = src[0] * src[6];
	tmp[9] = src[2] * src[4];
	tmp[10] = src[0] * src[5];
	tmp[11] = src[1] * src[4];

	dst[8] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
	dst[8] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
	dst[9] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
	dst[9] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
	dst[10] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
	dst[10] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
	dst[11] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
	dst[11] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
	dst[12] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
	dst[12] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
	dst[13] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
	dst[13] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
	dst[14] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
	dst[14] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
	dst[15] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
	dst[15] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];

	// Calculate determinant
	det = src[0] * dst[0] + src[1] * dst[1] + src[2] * dst[2] + src[3] * dst[3];

	// Inverse of matrix is divided by determinant
	det = 1 / det;
	for (int j = 0; j < 16; j++)
	{
		dst[j] *= det;
	}

	// Set it back
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m.mat[i][j] = dst[i * 4 + j];
		}
	}
}

	// Cast to a const float pointer
static inline const float* GetAsFloatPtr(const Matrix4Row& m)
{
	return reinterpret_cast<const float*>(&m.mat[0][0]);
}

static inline Vector3 GetTranslation(const Matrix4Row& m) 
{
	return Vector3(m.mat[3][0], m.mat[3][1], m.mat[3][2]);
}

static inline Vector3 GetXAxis(const Matrix4Row& m) 
{
	return Normalize(Vector3(m.mat[0][0], m.mat[0][1], m.mat[0][2]));
}

static inline Vector3 GetYAxis(const Matrix4Row& m) 
{
	return Normalize(Vector3(m.mat[1][0], m.mat[1][1], m.mat[1][2]));
}

static inline Vector3 GetZAxis(const Matrix4Row& m) 
{
	return Normalize(Vector3(m.mat[2][0], m.mat[2][1], m.mat[2][2]));
}

static inline Vector3 GetScale(const Matrix4Row& m) 
{
	Vector3 retVal = Vector3Zero();
	retVal.x = Length(Vector3(m.mat[0][0], m.mat[0][1], m.mat[0][2]));
	retVal.y = Length(Vector3(m.mat[1][0], m.mat[1][1], m.mat[1][2]));
	retVal.z = Length(Vector3(m.mat[2][0], m.mat[2][1], m.mat[2][2]));
	return retVal;
}

static inline  Matrix4Row Mat4RowCreateScale(float xScale, float yScale, float zScale)
{
	float temp[4][4] =
	{
		{ xScale, 0.0f, 0.0f, 0.0f },
		{ 0.0f, yScale, 0.0f, 0.0f },
		{ 0.0f, 0.0f, zScale, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};
	return Matrix4Row(temp);
}

static inline  Matrix4Row Mat4RowCreateScale(const Vector3& scaleVector)
{
	return Mat4RowCreateScale(scaleVector.x, scaleVector.y, scaleVector.z);
}

static inline  Matrix4Row Mat4RowCreateScale(float scale)
{
	return Mat4RowCreateScale(scale, scale, scale);
}

static inline  Matrix4Row Mat4RowCreateRotationX(float theta)
{
	float temp[4][4] =
	{
		{ 1.0f, 0.0f, 0.0f , 0.0f },
		{ 0.0f, Cos(theta), -Sin(theta), 0.0f },
		{ 0.0f, Sin(theta), Cos(theta), 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
	};
	return Matrix4Row(temp);
}

static inline  Matrix4Row Mat4RowCreateRotationY(float theta)
{
	float temp[4][4] =
	{
		{ Cos(theta), 0.0f, Sin(theta), 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ -Sin(theta), 0.0f, Cos(theta), 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
	};
	return Matrix4Row(temp);
}

static inline  Matrix4Row Mat4RowCreateRotationZ(float theta)
{
	float temp[4][4] =
	{
		{ Cos(theta), -Sin(theta), 0.0f, 0.0f },
		{ Sin(theta), Cos(theta), 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
	};
	return Matrix4Row(temp);
}

static inline  Matrix4Row Mat4RowCreateTranslation(const Vector3& trans)
{
	float temp[4][4] =
	{
		{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ trans.x, trans.y, trans.z, 1.0f }
	};
	return Matrix4Row(temp);
}

static inline  Matrix4Row Mat4RowCreateSimpleViewProj(float width, float height)
{
	float temp[4][4] =
	{
		{ 2.0f / width, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 2.0f / height, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f }
	};
	return Matrix4Row(temp);
}

static inline  Matrix4Row Mat4RowCreateFromQuaternion(const Quaternion& q)
{
	float mat[4][4];

	mat[0][0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
	mat[0][1] = 2.0f * q.x * q.y + 2.0f * q.w * q.z;
	mat[0][2] = 2.0f * q.x * q.z - 2.0f * q.w * q.y;
	mat[0][3] = 0.0f;

	mat[1][0] = 2.0f * q.x * q.y - 2.0f * q.w * q.z;
	mat[1][1] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
	mat[1][2] = 2.0f * q.y * q.z + 2.0f * q.w * q.x;
	mat[1][3] = 0.0f;

	mat[2][0] = 2.0f * q.x * q.z + 2.0f * q.w * q.y;
	mat[2][1] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
	mat[2][2] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;
	mat[2][3] = 0.0f;

	mat[3][0] = 0.0f;
	mat[3][1] = 0.0f;
	mat[3][2] = 0.0f;
	mat[3][3] = 1.0f;

	return Matrix4Row(mat);
}

static inline  Matrix4Row Mat4RowCreateLookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
{
	Vector3 zaxis = Normalize(target - eye);
	Vector3 xaxis = Normalize(Cross(up, zaxis));
	Vector3 yaxis = Normalize(Cross(zaxis, xaxis));
	Vector3 trans = Vector3Zero();
	trans.x = -Dot(xaxis, eye);
	trans.y = -Dot(yaxis, eye);
	trans.z = -Dot(zaxis, eye);

	float temp[4][4] =
	{
		{ xaxis.x, yaxis.x, zaxis.x, 0.0f },
		{ xaxis.y, yaxis.y, zaxis.y, 0.0f },
		{ xaxis.z, yaxis.z, zaxis.z, 0.0f },
		{ trans.x, trans.y, trans.z, 1.0f }
	};
	return Matrix4Row(temp);
}

static inline  Matrix4Row Mat4RowCreateOrtho(float width, float height, float near, float far)
{
	float temp[4][4] =
	{
		{ 1.0f / width, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f / height, 0.0f, 0.0f },
		{ 0.0f, 0.0f, -2.0f / (far - near), 0.0f },
		{ 0.0f, 0.0f, (far + near) / (near - far), 1.0f }
	};
	return Matrix4Row(temp);
}

static inline  Matrix4Row Mat4RowCreatePerspectiveFOV(float fovY, float width, float height, float near, float far)
{
	float yScale = Cot(fovY / 2.0f);
	float xScale = yScale * height / width;
	float temp[4][4] =
	{
		{ xScale, 0.0f, 0.0f, 0.0f },
		{ 0.0f, yScale, 0.0f, 0.0f },
		{ 0.0f, 0.0f, far / (far - near), 1.0f },
		{ 0.0f, 0.0f, -near * far / (far - near), 0.0f }
	};
	return Matrix4Row(temp);
}

static inline  Matrix4Row Mat4RowCreatePerspective(float left, float right, float bottom, float top, float near, float far)
{
	float temp[4][4] =
	{
		{ 2 * near / (right - left), 0.0f, 0.0f, 0.0f },
		{ 0.0f, 2 * near / (top - bottom), 0.0f, 0.0f },
		{ (right + left) / (right - left), (top + bottom) / (top - bottom), (far + near) / (near - far), -1.0f },
		{ 0.0f, 0.0f, 2 * near * far / (near - far), 0.0f }
	};
	return Matrix4Row(temp);
}

#endif // !MATHLIB_H