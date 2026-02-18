#include "cModel.h"

#include "Actor.h"
#include "Mesh.h"
#include "Scene.h"

Model::Model(Actor* _pOwner) :
	Component(_pOwner), mMesh(nullptr), mTextureIndex(0)
{
	mMesh = new Mesh();
	Scene::sActiveScene->getRendererGl()->AddModel(this);
}

Model::~Model()
{
	Scene::sActiveScene->getRendererGl()->RemoveModel(this);
}

void Model::Draw(Matrix4Row _viewProj)
{
	if (mMesh)
	{
		Matrix4Row wt = pOwner->getWorldTransform();
		mMesh->getShaderProgram()->Use();
		mMesh->getShaderProgram()->SetMatrix4Row("uViewProj", _viewProj);
		mMesh->getShaderProgram()->SetMatrix4Row("uWorldTransform", wt);
		Texture* t = mMesh->getTexture(mTextureIndex);
		if (t) t->SetActive();
		mMesh->getVertexArray()->SetActive();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}
