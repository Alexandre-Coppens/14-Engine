#include "Scene_Test.h"
#include "Assets.h"

#include "Shader.h"
#include "ShaderProgram.h"

#include "RendererGl.h"
#include "Log.h"
#include "BoxGl.h"
#include "Player3D.h"

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
	RendererGl* renderer = dynamic_cast<RendererGl*>(pRenderer);
	if (renderer == nullptr)
	{
		Log::Error(LogType::Video, "Renderer not of type OPENGL");
		return;
	}

	//Load Shaders
	Assets::LoadShader(renderer, "Resources/BasicModel.vert", "Resources/BasicModel.frag", "BasicModel");

	//Load Textures
	Assets::LoadTexture(*renderer, "Resources/Block.png", "Block");

	//Load Actors
	Actor* box = AddActor(new BoxGl());
	Actor* player = AddActor(new Player3D());
}

void Scene_Test::Update(float _deltaTime)
{
	Scene::Update(_deltaTime);
}

void Scene_Test::Close()
{
}