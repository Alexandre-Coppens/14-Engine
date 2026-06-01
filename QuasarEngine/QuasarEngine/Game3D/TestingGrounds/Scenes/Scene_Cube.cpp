#include "Scene_Cube.h"

#include "Engine/.Prefabs/Object.h"
#include "Engine/Utilitaries/Assets.h"
#include "Engine/Utilitaries/Log.h"

#include "Engine/Render/Shaders/Shader.h"
#include "Engine/Render/Shaders/ShaderProgram.h"
#include "Engine/Render/RendererGl.h"
#include "Game3D/Bowling/Actors/Player3D.h"
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

	//Load Actors
	Actor* cube = AddActor(new Object("Cube", OBJ_cube, PNG_Block, PROG_Planet_Base));
	Actor* player = AddActor(new Player3D());

	//Modify Actors
	player->getTransform3D()->addLocationX(-1.0f);
	cube->GetComponent<Model>()->getMaterial()->setDrawOption(DrawOption::TESSELATION);
	cube->GetComponent<Model>()->getMaterial()->SetFloat("", 5.0f);
}

void Scene_Cube::Update(float _deltaTime)
{
	Scene::Update(_deltaTime);
}

void Scene_Cube::Close()
{
	Scene::Close();
}