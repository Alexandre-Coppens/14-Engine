#include "Mesh.h"

#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Assets.h"

Mesh::Mesh():
	pVao(nullptr), mVerticesCount(28), mIndicesCount(36)
{
	pVao = new VertexArray(mVertices, mVerticesCount, mIndices, mIndicesCount);
}

Mesh::~Mesh() = default;

void Mesh::Unload()
{
	delete pVao;
	pVao = nullptr;
}
