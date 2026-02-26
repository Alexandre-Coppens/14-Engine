#include "Scene_Test.h"

#include "Engine/Utilitaries/Assets.h"
#include "Engine/Utilitaries/Log.h"

#include "Engine/Render/Shader.h"
#include "Engine/Render/ShaderProgram.h"
#include "Engine/Render/RendererGl.h"
#include "Game3D/Actors/BowlingAlley.h"

#include "Game3D/Actors/BoxGl.h"
#include "Game3D/Actors/Player3D.h"

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
	Assets::LoadShader(renderer, "BasicModel.vert", "Normal.frag", "Normal", TEXTURE);
	Assets::LoadShader(renderer, "BasicModel.vert", "Transparency.frag", "Transparency", COLOR);
	Assets::LoadShader(renderer, "Simple.vert", "Simple.frag", "Simple", COLOR);

	//LoadModels
	Assets::LoadMesh("Resources/Models/Cube.obj", "Cube");
	Assets::LoadMesh("Resources/Models/Bowling/Bowling_Alley_Rails.obj", "B_Rails");
	Assets::LoadMesh("Resources/Models/Bowling/Bowling_Alley_Walls.obj", "B_Walls");
	Assets::LoadMesh("Resources/Models/Bowling/Bowling_Alley_LightWalls.obj", "B_LightWalls");
	Assets::LoadMesh("Resources/Models/Bowling/Bowling_Alley_Carpet.obj", "B_Carpet");
	Assets::LoadMesh("Resources/Models/Bowling/Bowling_Alley_Panel.obj", "B_Panel");
	Assets::LoadMesh("Resources/Models/Bowling/Bowling_Alley_Alley.obj", "B_Alley");
	Assets::LoadMesh("Resources/Models/Bowling/Bowling_Alley_GutterTop.obj", "B_GutterTop");
	Assets::LoadMesh("Resources/Models/Bowling/Bowling_Alley_GutterBot.obj", "B_GutterBot");
	Assets::LoadMesh("Resources/Models/Bowling/Bowling_Alley_Back.obj", "B_Back");
	Assets::LoadMesh("Resources/Models/Bowling/Bowling_Alley_BallReturn.obj", "B_BallReturn");
	Assets::LoadMesh("Resources/Models/Bowling/Bowling_Alley_Balls.obj", "B_Balls");
	Assets::LoadMesh("Resources/Models/Bowling/Bowling_Alley_BallsStandee.obj", "B_BallsStandee");
	Assets::LoadMesh("Resources/Models/Bowling/Bowling_Alley_Bench.obj", "B_Bench");
	Assets::LoadMesh("Resources/Models/Bowling/Bowling_Alley_Chairs.obj", "B_Chairs");
	Assets::LoadMesh("Resources/Models/Bowling/Bowling_Alley_Decals.obj", "B_Decals");
	Assets::LoadMesh("Resources/Models/Bowling/Bowling_Alley_TableTop.obj", "B_TableTop");
	Assets::LoadMesh("Resources/Models/Bowling/Bowling_Alley_TableBot.obj", "B_TableBot");
	Assets::LoadMesh("Resources/Models/Bowling/Bowling_Alley_Trash.obj", "B_Trash");
	
	//Load Textures
	Assets::LoadTexture(*renderer, "Resources/Textures/Block.png", "Block");
	Assets::LoadTexture(*renderer, "Resources/Textures/Bowling/Bowling_Alley_Rails.png", "B_Rails");
	Assets::LoadTexture(*renderer, "Resources/Textures/Bowling/Bowling_Alley_Walls.png", "B_Walls");
	Assets::LoadTexture(*renderer, "Resources/Textures/Bowling/Bowling_Alley_Carpet.png", "B_Carpet");
	Assets::LoadTexture(*renderer, "Resources/Textures/Bowling/Bowling_Alley_Panel.png", "B_Panel");
	Assets::LoadTexture(*renderer, "Resources/Textures/Bowling/Bowling_Alley_Alley.png", "B_Alley");
	Assets::LoadTexture(*renderer, "Resources/Textures/Bowling/Bowling_Alley_GutterTop.png", "B_GutterTop");
	Assets::LoadTexture(*renderer, "Resources/Textures/Bowling/Bowling_Alley_GutterBot.png", "B_GutterBot");
	Assets::LoadTexture(*renderer, "Resources/Textures/Bowling/Bowling_Alley_Back.png", "B_Back");
	Assets::LoadTexture(*renderer, "Resources/Textures/Bowling/Bowling_Alley_BallReturn.png", "B_BallReturn");
	Assets::LoadTexture(*renderer, "Resources/Textures/Bowling/Bowling_Alley_Balls.png", "B_Balls");
	Assets::LoadTexture(*renderer, "Resources/Textures/Bowling/Bowling_Alley_BallsStandee.png", "B_BallsStandee");
	Assets::LoadTexture(*renderer, "Resources/Textures/Bowling/Bowling_Alley_Bench.png", "B_Bench");
	Assets::LoadTexture(*renderer, "Resources/Textures/Bowling/Bowling_Alley_Chairs.png", "B_Chairs");
	Assets::LoadTexture(*renderer, "Resources/Textures/Bowling/Bowling_Alley_Decals.png", "B_Decals");
	Assets::LoadTexture(*renderer, "Resources/Textures/Bowling/Bowling_Alley_TableTop.png", "B_TableTop");
	Assets::LoadTexture(*renderer, "Resources/Textures/Bowling/Bowling_Alley_TableBot.png", "B_TableBot");
	Assets::LoadTexture(*renderer, "Resources/Textures/Bowling/Bowling_Alley_Trash.png", "B_Trash");

	//Load Actors
	Actor* alley = AddActor(new BowlingAlley());
	Actor* player = AddActor(new Player3D());

	//Start the new Actors to modify them
	InitNewActors();

	//Modify Actors
	alley->getTransform3D()->addLocationZ(-0.25f);
}

void Scene_Test::Update(float _deltaTime)
{
	Scene::Update(_deltaTime);
}

void Scene_Test::Close()
{
}