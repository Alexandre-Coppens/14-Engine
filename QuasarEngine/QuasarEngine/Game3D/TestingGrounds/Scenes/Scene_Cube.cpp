#include "Scene_Cube.h"

#include "Engine/Utilitaries/Assets.h"
#include "Engine/Utilitaries/Log.h"

#include "Engine/Render/Shader.h"
#include "Engine/Render/ShaderProgram.h"
#include "Engine/Render/RendererGl.h"
#include "Game3D/TestingGrounds/Actors/ActorCamera.h"
#include "Game3D/TestingGrounds/Actors/Cube.h"

Scene_Cube::Scene_Cube(std::string _name)
{
}

Scene_Cube::~Scene_Cube()
{
}

void Scene_Cube::Start()
{
	Scene::Start();
	//Check Renderer Type
	RendererGl* renderer = dynamic_cast<RendererGl*>(pRenderer);
	if (renderer == nullptr)
	{
		Log::Error(LogType::Video, "Renderer not of type OPENGL");
		return;
	}

	//Load Shaders
	Assets::LoadShader(renderer, "BasicModel.vert", "BasicModel.frag", "BasicModel", TEXTURE);
	
	//LoadModels

	//Load Textures
	Assets::LoadTexture(*renderer, "Resources/Textures/Block.png", "Block");

	//Load Actors
	Actor* cube = AddActor(new Cube("Cube", "Cube", "Block", "BasicModel"));
	Actor* cube1 = AddActor(new Cube("Cube1", "Cube", "Block", "BasicModel"));
	Actor* player = AddActor(new ActorCamera());

	//Start the new Actors to modify them
	InitNewActors();

	//Modify Actors
	player->getTransform3D()->addLocationX(-1.0f);
	cube1->getTransform3D()->addLocationY(-1.0f);
}

void Scene_Cube::Update(float _deltaTime)
{
	Scene::Update(_deltaTime);
}

void Scene_Cube::Close()
{
	Scene::Close();
}