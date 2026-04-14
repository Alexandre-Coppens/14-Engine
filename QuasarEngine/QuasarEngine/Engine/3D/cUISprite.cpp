#include "cUISprite.h"

#include "Engine/Actor.h"
#include "Engine/Scene.h"
#include "Engine/Texture.h"
#include "Engine/3D/Mesh.h"

#include "Engine/Utilitaries/Assets.h"

#include "Engine/Render/ShaderProgram.h"
#include "Engine/Render/RendererGl.h"
#include "Engine/Render/VertexArray.h"
#include "Engine/Utilitaries/Time.h"

cUISprite::cUISprite(Actor* _pOwner, std::string _shader)  :
	Component(_pOwner)
{
	//Scene::ActiveScene->getRendererGl()->AddSprite(this, Assets::GetShaderProgram(mShader));
}

cUISprite::~cUISprite()
{
	Component::~Component();
}

void cUISprite::OnStart()
{
	Component::OnStart();
}

void cUISprite::Draw()
{
	if (!mVisible) return;
	glBindTexture(GL_TEXTURE_2D, 0);
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	float time = Time::currentFrameTime;
	Assets::GetShaderProgram(mShader)->SetFloat("uTime", time);
	
	Assets::GetShaderProgram(mShader)->SetVector4f("uColor", mColor);
	mTexture->SetActive();
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void cUISprite::Destroy()
{
	Component::Destroy();
}

//Remove the Model from his old ShaderList to a new one
void cUISprite::SetShader(const std::string _shader)
{
	//SScene::ActiveScene->getRendererGl()->RemoveModel(this, Assets::GetShaderProgram(mShader));
	mShader = _shader;
	//Scene::ActiveScene->getRendererGl()->AddModel(this, Assets::GetShaderProgram(mShader));
}
