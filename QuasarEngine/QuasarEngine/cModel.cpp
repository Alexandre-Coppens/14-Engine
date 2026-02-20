#include "cModel.h"

#include "Actor.h"
#include "Scene.h"
#include "ShaderProgram.h"
#include "RendererGl.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Mesh.h"

Model::Model(Actor* _pOwner) :
	Component(_pOwner), mMesh(nullptr), mTextureIndex(0)
{
	mMesh = new Mesh();
	Scene::ActiveScene->getRendererGl()->AddModel(this);
}

Model::~Model()
{
	Component::~Component();
	Scene::ActiveScene->getRendererGl()->RemoveModel(this);
}

void Model::Draw(const Matrix4Row _viewProj)
{
	if (mMesh)
	{
		const Matrix4Row wt = pOwner->getWorldTransform();
		mMesh->getShaderProgram()->Use();
		mMesh->getShaderProgram()->SetMatrix4Row("uViewProj", _viewProj);
		mMesh->getShaderProgram()->SetMatrix4Row("uWorldTransform", wt);
		const Texture* t = mMesh->getTexture(static_cast<Uint16>(mTextureIndex));
		if (t) t->SetActive();
		mMesh->getVertexArray()->SetActive();
		glDrawElements(GL_TRIANGLES, mMesh->getVertexArray()->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}
}
