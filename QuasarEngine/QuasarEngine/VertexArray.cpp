#include "VertexArray.h"
#include <glew.h>

VertexArray::VertexArray(const float* _pVertices, unsigned int _verticeCount, const unsigned int* _pIndices, unsigned int _indexCount) :
	mVerticeCount(_verticeCount), mIndexCount(_indexCount), mVertexArrayID(0), mVertexBufferID(0), mIndexBufferID(0)
{
	glGenVertexArrays(1, &mVertexArrayID);
	glBindVertexArray(mVertexArrayID);

	glGenBuffers(1, &mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, mVerticeCount * 3 * sizeof(float), _pVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &mIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);
	glBufferData(GL_ARRAY_BUFFER, mIndexCount * sizeof(float), _pIndices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBufferID);
	glDeleteBuffers(1, &mIndexBufferID);
	glDeleteBuffers(1, &mVertexArrayID);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArrayID);
}

