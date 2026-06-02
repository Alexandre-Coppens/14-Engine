#include "cModel.h"

#include "Engine/Actor.h"
#include "Engine/Scene.h"
#include "Engine/Texture.h"
#include "Engine/3D/Mesh.h"

#include "Engine/Utilitaries/Assets.h"

#include "Engine/Render/Shaders/ShaderProgram.h"
#include "Engine/Render/Shaders/Material.h"
#include "Engine/Render/RendererGl.h"
#include "Engine/Render/VertexArray.h"

Model::Model(Actor* _pOwner, GENERATED_SHADER_PROGRAMS _shader, DrawOption _option):
	Component(_pOwner),
	mMesh(nullptr),
	mMaterial(Material(Assets::GetShaderProgram(_shader), _option)),
	mParent(nullptr),
	option(_option)
{
	Scene::ActiveScene->getRendererGl()->AddModel(this, mMaterial.getShaderProgram());
}

Model::Model(Actor* _pOwner,Transform3D* _parent, GENERATED_SHADER_PROGRAMS _shader, DrawOption _option):
	Component(_pOwner),
	mMesh(nullptr),
	mMaterial(Material(Assets::GetShaderProgram(_shader), _option)),
	mParent(_parent),
	option(_option)
{
	Scene::ActiveScene->getRendererGl()->AddModel(this, mMaterial.getShaderProgram());
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

void Model::Draw()
{
	if (mMesh != nullptr)
	{
		if (!mVisible) return;
		const Matrix4Row wt = mParent->getWorldTransform();
		mMaterial.getShaderProgram()->SetMatrix4Row("uWorldTransform", wt);
		
		mMesh->getVertexArray()->SetActive();
		mMaterial.Bind();
		
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		 switch (mMaterial.getDrawOption())
		 {
		 case DrawOption::WIREFRAME:
		 	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		 	break;
		
		 case DrawOption::GEOMETRY:
		 	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		 	break;
		
		 case DrawOption::DEBUG:
		 	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		 	break;
		 	
		 case DrawOption::TESSELATION:
		 	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		 	break;
		 	
		 default:
		 	break;
		 }
		
		//glPointSize(5.0f);
		switch (mMaterial.getDrawOption())	
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
	Scene::ActiveScene->getRendererGl()->RemoveModel(this, mMaterial.getShaderProgram());
	mParent = nullptr;
	mMesh = nullptr;
	mMaterial.Unload();
	Component::Destroy();
}

//Remove the Model from his old ShaderList to a new one
void Model::SetShader(const GENERATED_SHADER_PROGRAMS _shader, DrawOption _option = DrawOption::NONE)
{
	Scene::ActiveScene->getRendererGl()->RemoveModel(this, mMaterial.getShaderProgram());
	mMaterial.Unload();
	mMaterial = Material(Assets::GetShaderProgram(_shader), _option);
	Scene::ActiveScene->getRendererGl()->AddModel(this, mMaterial.getShaderProgram());
}
