#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H
#include "Engine/Utilitaries/CommonLib.h"

constexpr float spriteVertices[] = {
	//POSITION                      NORMALS                     TEXCOORDS
	-0.5f, 0.5f, 0.0f,              0.0f, 0.0f, 0.0f,           0.0f, 0.0f,     //top left
	0.5f, 0.5f, 0.0f,               0.0f, 0.0f, 0.0f,           1.0f, 0.0f,     //top right
	-0.5f, -0.5f, 0.0f,             0.0f, 0.0f, 0.0f,           0.0f, 1.0f,      //bottom left
	0.5f, -0.5f, 0.0f,              0.0f, 0.0f, 0.0f,           1.0f, 1.0f,     //bottom right
 };

struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector2 texCoord;
	float* ToFloat() {
		float ret[8] = {
		position.x, position.y, position.z,
		normal.x, normal.y, normal.z,
		texCoord.x, texCoord.y};
		return ret;
	};
};

class VertexArray
{
private:
	unsigned int mVerticesCount;
	
	unsigned int mVertexArrayId;
	unsigned int mVertexBufferId;

public:
	unsigned int GetVerticesCount() const { return mVerticesCount; }

public:
	VertexArray(const float* _pVertices, unsigned int _verticesCount);
	~VertexArray();

	void SetActive() const;
};

#endif