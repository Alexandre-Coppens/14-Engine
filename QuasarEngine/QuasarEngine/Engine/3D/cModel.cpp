#include "cModel.h"

#include "Engine/Actor.h"
#include "Engine/Scene.h"
#include "Engine/Texture.h"
#include "Engine/3D/Mesh.h"

#include "Engine/Utilitaries/Assets.h"

#include "Engine/Render/ShaderProgram.h"
#include "Engine/Render/RendererGl.h"
#include "Engine/Render/VertexArray.h"

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

void Model::Draw(DrawOption _option)
{
	if (mMesh)
	{
		Texture* texture = nullptr;
		const Matrix4Row wt = pOwner->getWorldTransform();
		glBindTexture(GL_TEXTURE_2D, 0);
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		
		switch (_option)
		{
		case DrawOption::NULL_SHADER:
			texture = Assets::GetTexture("NULLSHADER");
			break;

		case DrawOption::TEXTURE:
			texture = mMesh->getTexture(static_cast<Uint16>(mTextureIndex));
			if (!texture) texture = Assets::GetTexture("NULLTEXTURE");
			break;
		
		case DrawOption::WIREFRAME:
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			break;

		case DrawOption::DEBUG:
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			break;
			
		case COLOR:
			break;
			
		default:
			break;
		}
		
		Assets::GetShader(mShader)->SetVector4f("uColor", mColor);
		if (texture != nullptr) texture->SetActive();

		Assets::GetShader(mShader)->SetMatrix4Row("uWorldTransform", wt);
		mMesh->getVertexArray()->SetActive();
		
		glPointSize(5.0f);
		glDrawArrays(GL_PATCHES, 0, mMesh->getVertexArray()->GetVerticesCount());
		//glDrawArrays(GL_TRIANGLES, 0, mMesh->getVertexArray()->GetVerticesCount());
	}
}

//Remove the Model from his old ShaderList to a new one
void Model::SetShader(const std::string _shader)
{
	Scene::ActiveScene->getRendererGl()->RemoveModel(this, Assets::GetShader(mShader));
	mShader = _shader;
	Scene::ActiveScene->getRendererGl()->AddModel(this, Assets::GetShader(mShader));
}
