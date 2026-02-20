#include "VertexArray.h"
#include <glew.h>

VertexArray::VertexArray(const float* _pVertices, const unsigned int _verticesCount, const unsigned int* _pIndices, unsigned int _indexCount) :
	mVerticesCount(_verticesCount), mIndexCount(_indexCount), mVertexArrayId(0), mVertexBufferId(0), mIndexBufferId(0)
{
	glGenVertexArrays(1, &mVertexArrayId);
	glBindVertexArray(mVertexArrayId);

	glGenBuffers(1, &mVertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, mVerticesCount * 5 * sizeof(float), _pVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &mIndexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndexCount * sizeof(float), _pIndices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBufferId);
	glDeleteBuffers(1, &mIndexBufferId);
	glDeleteBuffers(1, &mVertexArrayId);
}

void VertexArray::SetActive() const
{
	glBindVertexArray(mVertexArrayId);
}

