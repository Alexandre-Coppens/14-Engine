#ifndef COMMONLIB_H
#define COMMONLIB_H

#include <string>

//All Structs
struct Vector2
{
	float x;
	float y;
};

//Constants

static inline Vector2 Vector2Zero() 
{ 
	return Vector2{ 0.0f, 0.0f }; 
}

static inline Vector2 Vector2One()
{
	return Vector2{ 1.0f, 1.0f };
}

//Simple Functions

static inline std::string ToString(Vector2 v)
{
	return "( " + std::to_string(v.x) + ", " + std::to_string(v.y) + ")";
}
static inline Vector2 Add(Vector2 v1, Vector2 v2)
{
	return Vector2{ v1.x + v2.x, v1.y + v2.y };
}
static inline Vector2 Subtract(Vector2 v1, Vector2 v2)
{
	return Vector2{ v1.x - v2.x, v1.y - v2.y };
}
static inline Vector2 Multiply(Vector2 v1, Vector2 v2)
{
	return Vector2{ v1.x * v2.x, v1.y * v2.y };
}
static inline Vector2 Divide(Vector2 v1, Vector2 v2)
{
	return Vector2{ v1.x / v2.x, v1.y / v2.y };
}

#endif