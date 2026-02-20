#include "Scene_Test.h"
#include "Assets.h"

#include "Shader.h"
#include "ShaderProgram.h"

#include "RendererGl.h"
#include "Log.h"
#include "BoxGl.h"

Scene_Test::Scene_Test(std::string _name):
	Scene(std::move(_name))
{
}

Scene_Test::~Scene_Test()
{
}

void Scene_Test::Start()
{
	Scene::Start();
	mVertex = Shader(0, "Texture.vert", ShaderType::VERTEX);
	mFragment = Shader(0, "Texture.frag", ShaderType::FRAGMENT);

	RendererGl* renderer = dynamic_cast<RendererGl*>(pRenderer);
	if (renderer == nullptr)
	{
		Log::Error(LogType::Video, "Renderer not of type OPENGL");
		return;
	}
	mProgram.Compose(std::vector<Shader*>{&mVertex, & mFragment});
	renderer->setShaderProgram(&mProgram);
	mProgram.Use();

	Assets::LoadTexture(*renderer, "Resources/Block.png", "Block");

	Actor* player = AddActor(new BoxGl());
}

void Scene_Test::Update(float _deltaTime)
{
	Scene::Update(_deltaTime);
}

void Scene_Test::Close()
{
}