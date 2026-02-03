#pragma once

constexpr float vertices[] = {
-0.5f, 0.5f, 0.0f,	//A
0.5f, 0.5f, 0.0f,	//B
0.5f, -0.5f, 0.0f,	//C
-0.5f, -0.5f, 0.0f };	//D

constexpr unsigned int indices[] = {
0, 1, 2,
2, 3, 0
};


class VertexArray
{
private:
	unsigned int mVerticeCount;
	unsigned int mIndexCount;
	
	unsigned int mVertexArrayID;
	unsigned int mVertexBufferID;
	unsigned int mIndexBufferID;

public:
	unsigned int GetVerticeCount() const { return mVerticeCount; }
	unsigned int GetIndicesCount() const { return mIndexCount; }

public:
	VertexArray(const float* _pVertices, unsigned int _verticeCount, const unsigned int* _pIndices, unsigned int _indexCount);
	~VertexArray();

	void SetActive();
};