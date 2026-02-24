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
	Scene::ActiveScene->getRendererGl()->AddModel(this, Assets::GetShader(mShader));
}

Model::~Model()
{
	Component::~Component();
	Scene::ActiveScene->getRendererGl()->RemoveModel(this, Assets::GetShader(mShader));
}

void Model::Draw(int _option)
{
	if (mMesh)
	{
		const Matrix4Row wt = pOwner->getWorldTransform();
		Assets::GetShader(mShader)->SetMatrix4Row("uWorldTransform", wt);
		Texture* t;
		if (_option & DrawOption::NULL_SHADER)
		{
			t = Assets::GetTexture("NULLSHADER");
			if (t) t->SetActive();
		}
		else if (_option & DrawOption::TEXTURE)
		{
			t = mMesh->getTexture(static_cast<Uint16>(mTextureIndex));
			if (!t) t = Assets::GetTexture("NULLTEXTURE");
			if (t) t->SetActive();
		}
		if (_option & DrawOption::COLOR)
		{
			Assets::GetShader(mShader)->SetVector4f("uColor", Vector4(0.5f, 0.25f, 0.5f, 1.0f));
		}
		if (_option & DrawOption::DEBUG)
		{
			//TODO: Implement the debug draw box ON TOP of the mesh
		}
		mMesh->getVertexArray()->SetActive();
		glDrawArrays(GL_TRIANGLES, 0, mMesh->getVertexArray()->GetVerticesCount());
	}
}

//Remove the Model from his old ShaderList to a new one
void Model::SetShader(const std::string _shader)
{
	Scene::ActiveScene->getRendererGl()->RemoveModel(this, Assets::GetShader(mShader));
	mShader = _shader;
	Scene::ActiveScene->getRendererGl()->AddModel(this, Assets::GetShader(mShader));
}
