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
	
	//TODO: Auto load assets in folders
	
	//Load Shaders
	Assets::LoadShader(renderer, "BasicModel.vert", "BasicModel.frag", "BasicModel", TEXTURE);
	Assets::LoadShader(renderer, "Simple.vert", "Simple.frag", "Simple", COLOR);

	//LoadModels
	Assets::LoadMesh("Resources/Models/pin.obj", "Cube");
	
	//Load Textures
	Assets::LoadTexture(*renderer, "Resources/Block.png", "Block");

	//Load Actors
	Actor* box1 = AddActor(new BoxGl());
	Actor* box2 = AddActor(new BoxGl());
	Actor* box3 = AddActor(new BoxGl());
	Actor* player = AddActor(new Player3D());

	//Start the new Actors to modify them
	InitNewActors();
	
	dynamic_cast<BoxGl*>(box2)->getModel()->SetShader("Simple");
	dynamic_cast<BoxGl*>(box3)->getModel()->SetShader(" ");

	box2->getTransform3D()->addLocationX(2.5f);
	box3->getTransform3D()->addLocationY(3.0f);
	box3->getTransform3D()->addLocationZ(3.0f);
	box3->getTransform3D()->setScale(Vector3(2.0f));
}

void Scene_Test::Update(float _deltaTime)
{
	Scene::Update(_deltaTime);
}

void Scene_Test::Close()
{
}