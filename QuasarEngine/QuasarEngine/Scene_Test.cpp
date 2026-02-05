#include "Scene_Test.h"

#include "Shader.h"
#include "ShaderProgram.h"

#include "RendererGl.h"
#include "Log.h"

Scene_Test::Scene_Test(std::string _name)
{
}

void Scene_Test::Start()
{
	mVertex = Shader(0, "Basic.vert", ShaderType::VERTEX);
	mFragment = Shader(0, "Basic.frag", ShaderType::FRAGMENT);
	
	RendererGl* renderer = dynamic_cast<RendererGl*>(pRenderer);
	if (renderer == nullptr)
	{
		Log::Error(LogType::Video, "Renderer not of type OPENGL");
		return;
	}
	renderer->setShaderProgram(&mProgram);
}

void Scene_Test::Update(float _deltaTime)
{
}

void Scene_Test::Close()
{
}
