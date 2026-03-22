#include "VertexArray.h"
#include <glew.h>

#include "Engine/Utilitaries/DebugMemoryLeakCatcher.h"

VertexArray::VertexArray(const float* _pVertices, const unsigned int _verticesCount) :
	mVerticesCount(_verticesCount), mVertexArrayId(0), mVertexBufferId(0)
{
	//VAO
	glGenVertexArrays(1, &mVertexArrayId);
	glBindVertexArray(mVertexArrayId);

	//VBO
	glGenBuffers(1, &mVertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, mVerticesCount * 8 * sizeof(float), _pVertices, GL_STATIC_DRAW);

	//Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
	//Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
	//Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));

	DEBUGAddClass("VertexArray");
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBufferId);
	glDeleteBuffers(1, &mVertexArrayId);
	DEBUGRemoveClass("VertexArray");
}

void VertexArray::SetActive() const
{
	glBindVertexArray(mVertexArrayId);
}