#include "Scene_Bowling.h"

#include "Engine/Utilitaries/Assets.h"
#include "Engine/Utilitaries/Log.h"

#include "Engine/Render/Shader.h"
#include "Engine/Render/ShaderProgram.h"
#include "Engine/Render/RendererGl.h"

#include "Game3D/Bowling/Actors/Ball.h"
#include "Game3D/Bowling/Actors/BowlingAlley.h"
#include "Game3D/Bowling/Actors/Pin.h"

Scene_Bowling::Scene_Bowling(std::string _name):
	Scene(std::move(_name))
{
}

Scene_Bowling::~Scene_Bowling() = default;

void Scene_Bowling::Start()
{
	Scene::Start();
	RendererGl* renderer = dynamic_cast<RendererGl*>(pRenderer);
	if (renderer == nullptr)
	{
		Log::Error(LogType::Video, "Renderer not of type OPENGL");
		return;
	}
	
	//Load Shaders
	Assets::LoadShader(std::vector<GENERATED_SHADERS>{VERT_BasicModel, FRAG_BasicModel}, "BasicModel", DrawOption::TEXTURE);
	Assets::LoadShader(std::vector<GENERATED_SHADERS>{VERT_BasicModel, FRAG_Normal}, "Normal", DrawOption::TEXTURE);
	Assets::LoadShader(std::vector<GENERATED_SHADERS>{VERT_BasicModel, FRAG_Transparency}, "Transparency", DrawOption::TEXTURE);
	Assets::LoadShader(std::vector<GENERATED_SHADERS>{VERT_Simple, FRAG_Simple}, "Simple", DrawOption::COLOR);
	Assets::LoadShader(std::vector<GENERATED_SHADERS>{VERT_Simple, FRAG_Simple}, "Wireframe", DrawOption::WIREFRAME);

	//Load Actors
	Actor* alley = AddActor(new BowlingAlley());
	//Actor* player = AddActor(new Player3D());
	Actor* ball = AddActor(new Ball());
	
	Actor* pin1 = AddActor(new Pin());
	Actor* pin2 = AddActor(new Pin());
	Actor* pin3 = AddActor(new Pin());
	Actor* pin4 = AddActor(new Pin());
	Actor* pin5 = AddActor(new Pin());
	Actor* pin6 = AddActor(new Pin());
	Actor* pin7 = AddActor(new Pin());
	Actor* pin8 = AddActor(new Pin());
	Actor* pin9 = AddActor(new Pin());
	Actor* pin0 = AddActor(new Pin());

	//Start the new Actors to modify them
	InitNewActors();

	//Modify Actors
	alley->getTransform3D()->addLocationZ(-0.25f);
	ball->getTransform3D()->addLocationZ(-0.2f);
	
	pin1->getTransform3D()->setLocation(Vector3{-1.00f,  0.000f, -0.20f});
	pin1->getTransform3D()->addRotationZ(45.0f);
	pin2->getTransform3D()->setLocation(Vector3{-1.030f,  0.015f, -0.20f});
	pin2->getTransform3D()->addRotationZ(45.0f);
	pin3->getTransform3D()->setLocation(Vector3{-1.030f, -0.015f, -0.20f});
	pin3->getTransform3D()->addRotationZ(45.0f);
	pin4->getTransform3D()->setLocation(Vector3{-1.060f,  0.030f, -0.20f});
	pin5->getTransform3D()->setLocation(Vector3{-1.060f,  0.000f, -0.20f});
	pin6->getTransform3D()->setLocation(Vector3{-1.060f, -0.030f, -0.20f});
	pin7->getTransform3D()->setLocation(Vector3{-1.090f,  0.045f, -0.20f});
	pin8->getTransform3D()->setLocation(Vector3{-1.090f,  0.015f, -0.20f});
	pin9->getTransform3D()->setLocation(Vector3{-1.090f, -0.015f, -0.20f});
	pin0->getTransform3D()->setLocation(Vector3{-1.090f, -0.045f, -0.20f});
}

void Scene_Bowling::Update(float _deltaTime)
{
	Scene::Update(_deltaTime);
}

void Scene_Bowling::Close()
{
	Scene::Close();
}