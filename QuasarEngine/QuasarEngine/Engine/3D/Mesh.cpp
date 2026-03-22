#include "Mesh.h"

#include "Engine/Render/VertexArray.h"

Mesh::Mesh():
	pVao(nullptr)
{
	pVao = new VertexArray(spriteVertices, 4);
}

Mesh::Mesh(std::vector<Vertex> _vertices):
	mVertices(std::move(_vertices)), pVao(nullptr)
{
	float* verticeInfo = ToVerticeArray();
	pVao = new VertexArray(verticeInfo, mVertices.size());
	delete[] verticeInfo;
}

Mesh::~Mesh() = default;

void Mesh::Unload()
{
	delete pVao;
	pVao = nullptr;
}

float* Mesh::ToVerticeArray()
{
	float* array = new float[mVertices.size() * 8];
	int counter = 0;
	for (int i = 0; i < static_cast<int>(mVertices.size()); i++)
	{
		array[counter+0] = mVertices[i].position.x;
		array[counter+1] = mVertices[i].position.y;
		array[counter+2] = mVertices[i].position.z;
		array[counter+3] = mVertices[i].normal.x;
		array[counter+4] = mVertices[i].normal.y;
		array[counter+5] = mVertices[i].normal.z;
		array[counter+6] = mVertices[i].texCoord.x;
		array[counter+7] = mVertices[i].texCoord.y;
		counter += 8;
	}
	return array;
}
