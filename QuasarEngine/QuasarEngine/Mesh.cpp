#include "Mesh.h"

#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Assets.h"

Mesh::Mesh():
	pVao(nullptr), mVerticeCount(28), mIndicesCount(36)
{
	//int vSize = mVertices.size();
	//float vertices[];
	//copy(mVertices.begin(), mVertices.end(), vertices);

	pVao = new VertexArray(mVertices, mVerticeCount, mIndices, mIndicesCount);
	mVertexShader.Load("Texture.vert", ShaderType::VERTEX);
	mFragmentShader.Load("Texture.frag", ShaderType::FRAGMENT);
	mShaderProgram.Compose(std::vector<Shader*>{&mVertexShader, & mFragmentShader});
	pTextures.emplace_back(Assets::GetTexture("Block"));
}

Mesh::~Mesh()
{
}

void Mesh::Unload()
{
	delete pVao;
	pVao = nullptr;
}
