#ifndef COMMONLIB_H
#define COMMONLIB_H

#include <cstring>
#include <string>
#include <array>
#include <vector>

using std::array;

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	CENTER
};

//Break a string via a breaker
static inline std::vector<std::string> BreakString(std::string _str, char _breaker) {
	std::vector<std::string> r;
	std::string word;
	for(int i = 0; i < _str.size(); i++)
	{
		if (_str[i] == _breaker) {
			r.push_back(word);
			word.clear();
		}
		else{
			word += _str[i];
		}
	}
	r.push_back(word);
	return r;
}

//All Structs
struct Vector2
{
	float x, y;

	Vector2() : x(0.0f), y(0.0f) {};
	Vector2(float _f) : x(_f), y(_f) {};
	Vector2(float _x, float _y) : x(_x), y(_y) {};
};

struct Vector3
{
	float x, y, z;

	Vector3() : x(0.0f), y(0.0f), z(0.0f) {};
	Vector3(float _f) : x(_f), y(_f), z(_f) {};
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};
};

struct Vector4
{
	float x, y, z, w;

	Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {};
	Vector4(float _f) : x(_f), y(_f), z(_f), w(_f) {};
	Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {};
};

struct Quaternion
{
	float x, y, z, w;
	static const Quaternion QuatIdentity() { return Quaternion{ 0.0f, 0.0f, 0.0f, 1.0f }; }
	Quaternion() { *this = QuatIdentity(); }
	Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {};
};

struct Matrix4
{
	array<float, 16> mat;

	static const Matrix4 Mat4Identity() {
		return array < float, 16>{
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f};
	}
	Matrix4() { *this = Mat4Identity(); }
	Matrix4(const array<float, 16>& m4) {
		for (int n = 0; n < 16; ++n) {
			mat[n] = m4[n];
		}
	}
	float& operator()(int i, int j)
	{
		return mat[i * 4 + j];
	}
	const float& operator()(int i, int j) const
	{
		return mat[i * 4 + j];
	}
	inline Matrix4& operator=(const Matrix4& m)
	{
		for (int n = 0; n < 16; ++n) {
			mat[n] = m.mat[n];
		}
		return *this;
	}
};

struct Matrix4Row
{
	float mat[4][4];

	inline static float m4IdentRow[4][4] =
	{
		{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};
	static inline Matrix4Row Mat4RowIdentity()
	{
		return m4IdentRow;
	}
	Matrix4Row() { *this = Mat4RowIdentity(); }
	Matrix4Row(float inMat[4][4]) { memcpy(mat, inMat, 16 * sizeof(float));	}
};

//-=- CONSTANTS -=-
//Vector 2

static const Vector2 Vector2Zero() { return Vector2{ 0.0f, 0.0f }; }
static const Vector2 Vector2One()  { return Vector2{ 1.0f, 1.0f }; }

//Vector 3

static const Vector3 Vector3Zero()	{ return Vector3{ 0.0f, 0.0f, 0.0f }; }
static const Vector3 Vector3One()	{ return Vector3{ 1.0f, 1.0f, 1.0f }; }
static const Vector3 Vector3UnitX()	{ return Vector3{ 1.0f, 0.0f, 0.0f }; }
static const Vector3 Vector3UnitY() { return Vector3{ 0.0f, 1.0f, 0.0f }; }
static const Vector3 Vector3UnitZ() { return Vector3{ 0.0f, 0.0f, 1.0f }; }
static const Vector3 Vector3NegUnitX() { return Vector3{ -1.0f, 0.0f, 0.0f }; }
static const Vector3 Vector3NegUnitY() { return Vector3{ 0.0f, -1.0f, 0.0f }; }
static const Vector3 Vector3NegUnitZ() { return Vector3{ 0.0f, 0.0f, -1.0f }; }

//Vector 4

static const Vector4 Vector4Zero() { return Vector4{ 0.0f, 0.0f, 0.0f, 0.0f }; }
static const Vector4 Vector4One() { return Vector4{ 1.0f, 1.0f, 1.0f, 1.0f }; }

//Quaternion

//Matrix 4

//Matrix4Row

//-=- SIMPLE FUNCTIONS -=-
//Vector 2

static inline std::string ToString(Vector2 v)
{
	return "( " + std::to_string(v.x) + ", " + std::to_string(v.y) + ")";
}

static inline Vector2 AddScalar(Vector2 v1, float f)
{
	return Vector2{ v1.x + f, v1.y + f };
}
static inline Vector2 Add(Vector2 v1, Vector2 v2)
{
	return Vector2{ v1.x + v2.x, v1.y + v2.y };
}
inline Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
	return Add(v1, v2);
}
inline Vector2 operator+=(Vector2& v1, Vector2& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}

static inline Vector2 SubtractScalar(Vector2 v1, float f)
{
	return Vector2{ v1.x - f, v1.y - f };
}
static inline Vector2 Subtract(Vector2 v1, Vector2 v2)
{
	return Vector2{ v1.x - v2.x, v1.y - v2.y };
}
inline Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
	return Subtract(v1, v2);
}
inline Vector2 operator-=(Vector2& v1, Vector2& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	return v1;
}

static inline Vector2 MultiplyScalar(Vector2 v1, float f)
{
	return Vector2{ v1.x * f, v1.y * f };
}
static inline Vector2 Multiply(Vector2 v1, Vector2 v2)
{
	return Vector2{ v1.x * v2.x, v1.y * v2.y };
}
inline Vector2 operator*(const Vector2& v1, const Vector2& v2)
{
	return Multiply(v1, v2);
}
inline Vector2 operator*(const Vector2& v, const float f)
{
	return MultiplyScalar(v, f);
}
inline Vector2 operator*(const float f, const Vector2& v)
{
	return MultiplyScalar(v, f);
}
inline Vector2& operator*=(Vector2& v, float f) {
	v.x *= f;
	v.y *= f;
	return v;
}

static inline Vector2 DivideScalar(Vector2 v1, float f)
{
	return Vector2{ v1.x / f, v1.y / f };
}
static inline Vector2 Divide(Vector2 v1, Vector2 v2)
{
	return Vector2{ v1.x / v2.x, v1.y / v2.y };
}
inline Vector2 operator/(const Vector2& v1, const Vector2& v2)
{
	return Divide(v1, v2);
}

static inline bool Equal(Vector2 v1, Vector2 v2)
{
	return v1.x == v2.x && v1.y == v2.y;
}
inline bool operator==(const Vector2& v1, const Vector2& v2)
{
	return Equal(v1, v2);
}



//Vector 3
static inline std::string ToString(Vector3 v)
{
	return "( " + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ")";
}

static inline Vector3 AddScalar(Vector3 v1, float f)
{
	return Vector3{ v1.x + f, v1.y + f, v1.z + f };
}
static inline Vector3 Add(Vector3 v1, Vector3 v2)
{
	return Vector3{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}
inline Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	return Add(v1, v2);
}
inline Vector3 operator+=(Vector3& v1, Vector3 v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return v1;
}

static inline Vector3 SubtractScalar(Vector3 v1, float f)
{
	return Vector3{ v1.x - f, v1.y - f, v1.z - f };
}
static inline Vector3 Subtract(Vector3 v1, Vector3 v2)
{
	return Vector3{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}
inline Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	return Subtract(v1, v2);
}
inline Vector3 operator-=(Vector3& v1, Vector3& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return v1;
}

static inline Vector3 MultiplyScalar(const Vector3& v1, const float& f)
{
	return Vector3{ v1.x * f, v1.y * f, v1.z * f };
}
static inline Vector3 Multiply(Vector3 v1, Vector3 v2)
{
	return Vector3{ v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
}
inline Vector3 operator*(const Vector3& v1, const Vector3& v2)
{
	return Multiply(v1, v2);
}
inline Vector3 operator*(const float& f, const Vector3& v1)
{
	return MultiplyScalar(v1, f);
}
inline Vector3 operator*(const Vector3& v1, const float& f)
{
	return MultiplyScalar(v1, f);
}
inline Vector3& operator*=(Vector3& v1, Vector3 v2) {
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
	return v1;
}
inline Vector3& operator*=(Vector3& v, float f) {
	v.x *= f;
	v.y *= f;
	v.z *= f;
	return v;
}

static inline Vector3 DivideScalar(Vector3 v1, float f)
{
	return Vector3{ v1.x / f, v1.y / f, v1.z / f };
}
static inline Vector3 Divide(Vector3 v1, Vector3 v2)
{
	return Vector3{ v1.x / v2.x, v1.y / v2.y, v1.z / v2.z };
}
inline Vector3 operator/(const Vector3& v1, const Vector3& v2)
{
	return Divide(v1, v2);
}

static inline bool Equal(Vector3 v1, Vector3 v2)
{
	return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}
inline bool operator==(const Vector3& v1, const Vector3& v2)
{
	return Equal(v1, v2);
}

//Vector 4
static inline std::string ToString(Vector4 v)
{
	return "( " + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ", " + std::to_string(v.w) + ")";
}

static inline Vector4 AddScalar(Vector4 v1, float f)
{
	return Vector4{ v1.x + f, v1.y + f, v1.z + f, v1.w + f };
}
static inline Vector4 Add(Vector4 v1, Vector4 v2)
{
	return Vector4{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w };
}
inline Vector4 operator+(const Vector4& v1, const Vector4& v2)
{
	return Add(v1, v2);
}
inline Vector4 operator+=(Vector4& v1, Vector4 v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	v1.w += v2.w;
	return v1;
}

static inline Vector4 SubtractScalar(Vector4 v1, float f)
{
	return Vector4{ v1.x - f, v1.y - f, v1.z - f, v1.w - f };
}
static inline Vector4 Subtract(Vector4 v1, Vector4 v2)
{
	return Vector4{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w };
}
inline Vector4 operator-(const Vector4& v1, const Vector4& v2)
{
	return Subtract(v1, v2);
}
inline Vector4 operator-=(Vector4& v1, Vector4& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	v1.w -= v2.w;
	return v1;
}

static inline Vector4 MultiplyScalar(Vector4 v1, float f)
{
	return Vector4{ v1.x * f, v1.y * f, v1.z * f, v1.w * f };
}
static inline Vector4 Multiply(Vector4 v1, Vector4 v2)
{
	return Vector4{ v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w };
}
inline Vector4 operator*(const Vector4& v1, const Vector4& v2)
{
	return Multiply(v1, v2);
}
inline Vector4 operator*(const float& f, const Vector4& v1)
{
	return MultiplyScalar(v1, f);
}
inline Vector4 operator*(const Vector4& v1, const float& f)
{
	return MultiplyScalar(v1, f);
}
inline Vector4& operator*=(Vector4& v, float f) {
	v.x *= f;
	v.y *= f;
	v.z *= f;
	v.w *= f;
	return v;
}

static inline Vector4 DivideScalar(Vector4 v1, float f)
{
	return Vector4{ v1.x / f, v1.y / f, v1.z / f, v1.w / f };
}
static inline Vector4 Divide(Vector4 v1, Vector4 v2)
{
	return Vector4{ v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w };
}
inline Vector4 operator/(const Vector4& v1, const Vector4& v2)
{
	return Divide(v1, v2);
}

static inline bool Equal(Vector4 v1, Vector4 v2)
{
	return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
}
inline bool operator==(const Vector4& v1, const Vector4& v2)
{
	return Equal(v1, v2);
}

//Quaternion
static inline std::string ToString(Quaternion v)
{
	return "( " + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ", " + std::to_string(v.w) + ")";
}

static inline Quaternion Multiply(Quaternion q1, Quaternion q2)
{
	return Quaternion{ 
		q1.x*q2.w + q1.y*q2.z - q1.z*q2.y + q1.w*q2.x,
		q1.y*q2.w + q1.z*q2.x + q1.w*q2.y - q1.x*q2.z,
		q1.z*q2.w + q1.w*q2.z + q1.x*q2.y - q1.y*q2.x,
		q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z
	};
}
inline Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
{
	return Multiply(q1, q2);
}
inline Quaternion& operator*=(Quaternion& q1, Quaternion q2) {
	return q1 = Multiply(q1, q2);
}


//Matrix4

static inline Matrix4 operator+(const Matrix4& m1, const Matrix4& m2)
{
	Matrix4 result;
	int n;
	for (n = 0; n < 16; n++)
		result.mat[n] = m1.mat[n] + m2.mat[n];
	return result;
}

static inline Matrix4& operator+=(Matrix4& m1, Matrix4& m2)
{
	return (m1 = m1 + m2);
}

static inline Matrix4 operator-(const Matrix4& m1, const Matrix4& m2)
{
	Matrix4 result;
	int n;
	for (n = 0; n < 16; n++)
		result.mat[n] = m1.mat[n] - m2.mat[n];
	return result;
}

static inline Matrix4& operator-=(Matrix4& m1, Matrix4& m2)
{
	return (m1 = m1 - m2);
}

// Matrix multiplication (a * b)
static inline Matrix4 operator*(const Matrix4& a, const Matrix4& b)
{
	Matrix4 retVal;

	retVal(0, 0) =
		a(0, 0) * b(0, 0) +
		a(1, 0) * b(0, 1) +
		a(2, 0) * b(0, 2) +
		a(3, 0) * b(0, 3);

	retVal(0, 1) =
		a(0, 1) * b(0, 0) +
		a(1, 1) * b(0, 1) +
		a(2, 1) * b(0, 2) +
		a(3, 1) * b(0, 3);

	retVal(0, 2) =
		a(0, 2) * b(0, 0) +
		a(1, 2) * b(0, 1) +
		a(2, 2) * b(0, 2) +
		a(3, 2) * b(0, 3);

	retVal(0, 3) =
		a(0, 3) * b(0, 0) +
		a(1, 3) * b(0, 1) +
		a(2, 3) * b(0, 2) +
		a(3, 3) * b(0, 3);

	retVal(1, 0) =
		a(0, 0) * b(1, 0) +
		a(1, 0) * b(1, 1) +
		a(2, 0) * b(1, 2) +
		a(3, 0) * b(1, 3);

	retVal(1, 1) =
		a(0, 1) * b(1, 0) +
		a(1, 1) * b(1, 1) +
		a(2, 1) * b(1, 2) +
		a(3, 1) * b(1, 3);

	retVal(1, 2) =
		a(0, 2) * b(1, 0) +
		a(1, 2) * b(1, 1) +
		a(2, 2) * b(1, 2) +
		a(3, 2) * b(1, 3);

	retVal(1, 3) =
		a(0, 3) * b(1, 0) +
		a(1, 3) * b(1, 1) +
		a(2, 3) * b(1, 2) +
		a(3, 3) * b(1, 3);

	retVal(2, 0) =
		a(0, 0) * b(2, 0) +
		a(1, 0) * b(2, 1) +
		a(2, 0) * b(2, 2) +
		a(3, 0) * b(2, 3);

	retVal(2, 1) =
		a(0, 1) * b(2, 0) +
		a(1, 1) * b(2, 1) +
		a(2, 1) * b(2, 2) +
		a(3, 1) * b(2, 3);

	retVal(2, 2) =
		a(0, 2) * b(2, 0) +
		a(1, 2) * b(2, 1) +
		a(2, 2) * b(2, 2) +
		a(3, 2) * b(2, 3);

	retVal(2, 3) =
		a(0, 3) * b(2, 0) +
		a(1, 3) * b(2, 1) +
		a(2, 3) * b(2, 2) +
		a(3, 3) * b(2, 3);

	retVal(3, 0) =
		a(0, 0) * b(3, 0) +
		a(1, 0) * b(3, 1) +
		a(2, 0) * b(3, 2) +
		a(3, 0) * b(3, 3);

	retVal(3, 1) =
		a(0, 1) * b(3, 0) +
		a(1, 1) * b(3, 1) +
		a(2, 1) * b(3, 2) +
		a(3, 1) * b(3, 3);

	retVal(3, 2) =
		a(0, 2) * b(3, 0) +
		a(1, 2) * b(3, 1) +
		a(2, 2) * b(3, 2) +
		a(3, 2) * b(3, 3);

	retVal(3, 3) =
		a(0, 3) * b(3, 0) +
		a(1, 3) * b(3, 1) +
		a(2, 3) * b(3, 2) +
		a(3, 3) * b(3, 3);

	return retVal;
}

inline Matrix4& operator*=(Matrix4& m1, Matrix4& m2)
{
	m1 = m1 * m2;
	return m1;
}

//Matrix4Row

static inline Matrix4Row operator*(const Matrix4Row& a, const Matrix4Row& b)
{
	Matrix4Row retVal;
	// row 0
	retVal.mat[0][0] =
		a.mat[0][0] * b.mat[0][0] +
		a.mat[0][1] * b.mat[1][0] +
		a.mat[0][2] * b.mat[2][0] +
		a.mat[0][3] * b.mat[3][0];

	retVal.mat[0][1] =
		a.mat[0][0] * b.mat[0][1] +
		a.mat[0][1] * b.mat[1][1] +
		a.mat[0][2] * b.mat[2][1] +
		a.mat[0][3] * b.mat[3][1];

	retVal.mat[0][2] =
		a.mat[0][0] * b.mat[0][2] +
		a.mat[0][1] * b.mat[1][2] +
		a.mat[0][2] * b.mat[2][2] +
		a.mat[0][3] * b.mat[3][2];

	retVal.mat[0][3] =
		a.mat[0][0] * b.mat[0][3] +
		a.mat[0][1] * b.mat[1][3] +
		a.mat[0][2] * b.mat[2][3] +
		a.mat[0][3] * b.mat[3][3];

	// row 1
	retVal.mat[1][0] =
		a.mat[1][0] * b.mat[0][0] +
		a.mat[1][1] * b.mat[1][0] +
		a.mat[1][2] * b.mat[2][0] +
		a.mat[1][3] * b.mat[3][0];

	retVal.mat[1][1] =
		a.mat[1][0] * b.mat[0][1] +
		a.mat[1][1] * b.mat[1][1] +
		a.mat[1][2] * b.mat[2][1] +
		a.mat[1][3] * b.mat[3][1];

	retVal.mat[1][2] =
		a.mat[1][0] * b.mat[0][2] +
		a.mat[1][1] * b.mat[1][2] +
		a.mat[1][2] * b.mat[2][2] +
		a.mat[1][3] * b.mat[3][2];

	retVal.mat[1][3] =
		a.mat[1][0] * b.mat[0][3] +
		a.mat[1][1] * b.mat[1][3] +
		a.mat[1][2] * b.mat[2][3] +
		a.mat[1][3] * b.mat[3][3];

	// row 2
	retVal.mat[2][0] =
		a.mat[2][0] * b.mat[0][0] +
		a.mat[2][1] * b.mat[1][0] +
		a.mat[2][2] * b.mat[2][0] +
		a.mat[2][3] * b.mat[3][0];

	retVal.mat[2][1] =
		a.mat[2][0] * b.mat[0][1] +
		a.mat[2][1] * b.mat[1][1] +
		a.mat[2][2] * b.mat[2][1] +
		a.mat[2][3] * b.mat[3][1];

	retVal.mat[2][2] =
		a.mat[2][0] * b.mat[0][2] +
		a.mat[2][1] * b.mat[1][2] +
		a.mat[2][2] * b.mat[2][2] +
		a.mat[2][3] * b.mat[3][2];

	retVal.mat[2][3] =
		a.mat[2][0] * b.mat[0][3] +
		a.mat[2][1] * b.mat[1][3] +
		a.mat[2][2] * b.mat[2][3] +
		a.mat[2][3] * b.mat[3][3];

	// row 3
	retVal.mat[3][0] =
		a.mat[3][0] * b.mat[0][0] +
		a.mat[3][1] * b.mat[1][0] +
		a.mat[3][2] * b.mat[2][0] +
		a.mat[3][3] * b.mat[3][0];

	retVal.mat[3][1] =
		a.mat[3][0] * b.mat[0][1] +
		a.mat[3][1] * b.mat[1][1] +
		a.mat[3][2] * b.mat[2][1] +
		a.mat[3][3] * b.mat[3][1];

	retVal.mat[3][2] =
		a.mat[3][0] * b.mat[0][2] +
		a.mat[3][1] * b.mat[1][2] +
		a.mat[3][2] * b.mat[2][2] +
		a.mat[3][3] * b.mat[3][2];

	retVal.mat[3][3] =
		a.mat[3][0] * b.mat[0][3] +
		a.mat[3][1] * b.mat[1][3] +
		a.mat[3][2] * b.mat[2][3] +
		a.mat[3][3] * b.mat[3][3];

	return retVal;
}

inline Matrix4Row& operator*=( Matrix4Row& m1, const Matrix4Row& m2)
{
	m1 = m1 * m2;
	return m1;
}

#endif