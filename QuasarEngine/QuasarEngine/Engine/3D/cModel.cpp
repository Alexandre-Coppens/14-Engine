#include "cModel.h"

#include "Engine/Actor.h"
#include "Engine/Scene.h"
#include "Engine/Texture.h"
#include "Engine/3D/Mesh.h"

#include "Engine/Utilitaries/Assets.h"

#include "Engine/Render/ShaderProgram.h"
#include "Engine/Render/RendererGl.h"
#include "Engine/Render/VertexArray.h"
#include "Engine/Utilitaries/Time.h"

Model::Model(Actor* _pOwner, std::string _shader)  :
	Component(_pOwner), mMesh(nullptr), mTextureIndex(0), mShader(_shader), mParent(nullptr)
{
	Scene::ActiveScene->getRendererGl()->AddModel(this, Assets::GetShaderProgram(mShader));
}

Model::Model(Actor* _pOwner,Transform3D* _parent, std::string _shader)  :
	Component(_pOwner), mMesh(nullptr), mTextureIndex(0), mShader(_shader), mParent(_parent)
{
	Scene::ActiveScene->getRendererGl()->AddModel(this, Assets::GetShaderProgram(mShader));
}

Model::~Model()
{
	Component::~Component();
}

void Model::OnStart()
{
	if (mParent == nullptr) mParent = pOwner->getTransform3D();
	Component::OnStart();
}

void Model::Draw(DrawOption _option)
{
	if (mMesh)
	{
		if (!mVisible) return;
		Texture* texture = nullptr;
		const Matrix4Row wt = mParent->getWorldTransform();
		glBindTexture(GL_TEXTURE_2D, 0);
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		
		switch (_option)
		{
		case DrawOption::NULL_SHADER:
			texture = Assets::GetTexture(PNG_NullShader);
			break;

		case DrawOption::TEXTURE:
			texture = mMesh->getTexture(static_cast<Uint16>(mTextureIndex));
			if (!texture) texture = Assets::GetTexture(PNG_NullTexture);
			break;
		
		case DrawOption::WIREFRAME:
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			break;
			
		case DrawOption::TESSELATION:
			//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			texture = mMesh->getTexture(static_cast<Uint16>(mTextureIndex));
			if (!texture) texture = Assets::GetTexture(PNG_NullTexture);
			break;

		case DrawOption::GEOMETRY:
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			break;

		case DrawOption::INSTANCED:
			texture = mMesh->getTexture(static_cast<Uint16>(mTextureIndex));
			if (!texture) texture = Assets::GetTexture(PNG_NullTexture);
			break;

		case DrawOption::DEBUG:
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			break;
			
		case DrawOption::COLOR:
			break;
			
		default:
			break;
		}

		float time = Time::currentFrameTime;
		Assets::GetShaderProgram(mShader)->SetFloat("uTime", time);
		
		Assets::GetShaderProgram(mShader)->SetVector4f("uColor", mColor);
		if (texture != nullptr) texture->SetActive();

		Assets::GetShaderProgram(mShader)->SetMatrix4Row("uWorldTransform", wt);
		mMesh->getVertexArray()->SetActive();
		
		//glPointSize(5.0f);
		switch (_option)
		{
		case DrawOption::INSTANCED:
			glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, mMesh->getVertexArray()->GetVerticesCount(), 1024 * 1024);
			break;
			
		case DrawOption::TESSELATION:
			glDrawArrays(GL_PATCHES, 0, mMesh->getVertexArray()->GetVerticesCount());
			break;
			
		default:
			glDrawArrays(GL_TRIANGLES, 0, mMesh->getVertexArray()->GetVerticesCount());
			break;
		}
	}
}
void Model::Destroy()
{
	Scene::ActiveScene->getRendererGl()->RemoveModel(this, Assets::GetShaderProgram(mShader));
	mParent = nullptr;
	mMesh = nullptr;
	Component::Destroy();
}

//Remove the Model from his old ShaderList to a new one
void Model::SetShader(const std::string _shader)
{
	Scene::ActiveScene->getRendererGl()->RemoveModel(this, Assets::GetShaderProgram(mShader));
	mShader = _shader;
	Scene::ActiveScene->getRendererGl()->AddModel(this, Assets::GetShaderProgram(mShader));
}
