#include "cModel.h"

#include "Actor.h"
#include "Assets.h"
#include "Scene.h"
#include "ShaderProgram.h"
#include "RendererGl.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Mesh.h"

Model::Model(Actor* _pOwner, std::string _shader)  :
	Component(_pOwner), mMesh(nullptr), mTextureIndex(0), mShader(_shader)
{
	mMesh = new Mesh();
	Scene::ActiveScene->getRendererGl()->AddModel(this, Assets::GetShader(mShader));
}

Model::~Model()
{
	Component::~Component();
	Scene::ActiveScene->getRendererGl()->RemoveModel(this, Assets::GetShader(mShader));
}

void Model::Draw()
{
	if (mMesh)
	{
		const Matrix4Row wt = pOwner->getWorldTransform();
		Assets::GetShader(mShader)->SetMatrix4Row("uWorldTransform", wt);
		const Texture* t = mMesh->getTexture(static_cast<Uint16>(mTextureIndex));
		if (t) t->SetActive();
		mMesh->getVertexArray()->SetActive();
		glDrawElements(GL_TRIANGLES, mMesh->getVertexArray()->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}
}

//Remove the Model from his old ShaderList to a new one
void Model::SetShader(const std::string _shader)
{
	Scene::ActiveScene->getRendererGl()->RemoveModel(this, Assets::GetShader(mShader));
	mShader = _shader;
	Scene::ActiveScene->getRendererGl()->AddModel(this, Assets::GetShader(mShader));
}
