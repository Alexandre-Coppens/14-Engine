#include "Mesh.h"

#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Assets.h"

Mesh::Mesh():
	pVao(nullptr), mVerticesCount(28), mIndicesCount(36)
{
	//int vSize = mVertices.size();
	//float vertices[];
	//copy(mVertices.begin(), mVertices.end(), vertices);

	pVao = new VertexArray(mVertices, mVerticesCount, mIndices, mIndicesCount);
	mVertexShader.Load("BasicModel.vert", ShaderType::VERTEX);
	mFragmentShader.Load("BasicModel.frag", ShaderType::FRAGMENT);
	mShaderProgram.Compose(std::vector<Shader*>{&mVertexShader, & mFragmentShader});
	pTextures.emplace_back(Assets::GetTexture("Block"));
}

Mesh::~Mesh() = default;

void Mesh::Unload()
{
	delete pVao;
	pVao = nullptr;
}
