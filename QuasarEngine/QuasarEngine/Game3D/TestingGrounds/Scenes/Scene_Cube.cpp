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
#include "Game3D/TestingGrounds/Actors/Planet.h"

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
	Actor* sun = AddActor(new Object("Sun", OBJ_cube, PNG_NullTexture, PROG_Planet_Sun));
	Actor* treePlanet = AddActor(new Planet( OBJ_cube,PROG_Planet_Beach, PNG_Block, 3.0f, sun, 0.1f));
	Actor* trees = AddActor(new Planet( OBJ_Tree,PROG_Planet_Beach_Tree, PNG_Planet_Tree, 3.0f, sun, 0.1f));
	Actor* rockPlanet = AddActor(new Planet( OBJ_cube,PROG_Planet_Rock, PNG_Block, 3.0f, treePlanet, 0.3f));
	Actor* stars = AddActor(new Planet( OBJ_cube,PROG_Planet_Stars, PNG_Star_Sheet, 0.0f, sun, 0.0f));
	Actor* asteroids = AddActor(new Planet( OBJ_cube,PROG_Planet_Asteroids, PNG_Star_Sheet, 0.0f, sun, 0.0f));
	Actor* player = AddActor(new Player3D());

	//Modify Actors
	player->getTransform3D()->addLocationX(25.0f);
	player->getTransform3D()->addLocationZ(4.0f);
	
	sun->GetComponent<Model>()->getMaterial()->setDrawOption(DrawOption::TESSELATION);
	sun->GetComponent<Model>()->getMaterial()->SetFloat("uSphereRadius", 10.0f);
	sun->GetComponent<Model>()->getMaterial()->SetFloat("uNoiseStrength", 0.05f);
	sun->GetComponent<Model>()->getMaterial()->SetFloat("uNoiseSize", 5.0f);
	
	treePlanet->getTransform3D()->addLocationX(15.0f); 
	treePlanet->getTransform3D()->addRotation(Vector3(35.0f, 50.0f, 0.0f));
	treePlanet->GetComponent<Model>()->getMaterial()->setDrawOption(DrawOption::TESSELATION);
	treePlanet->GetComponent<Model>()->getMaterial()->SetFloat("uSphereRadius", 1.0f);
	treePlanet->GetComponent<Model>()->getMaterial()->SetFloat("uNoiseStrength", 0.25f);
	treePlanet->GetComponent<Model>()->getMaterial()->SetFloat("uNoiseSize", 2.0f);
	
	trees->getTransform3D()->addLocationX(15.0f); 
	trees->getTransform3D()->addRotation(Vector3(35.0f, 50.0f, 0.0f));
	trees->getTransform3D()->setScale(0.1f);
	trees->GetComponent<Model>()->getMaterial()->setDrawOption(DrawOption::INSTANCED);
	trees->GetComponent<Model>()->getMaterial()->SetInteger("uInstances", 50 * 25);
	trees->GetComponent<Model>()->getMaterial()->SetFloat("uSphereRadius", 1.0f);
	trees->GetComponent<Model>()->getMaterial()->SetFloat("uNoiseStrength", 0.25f);
	trees->GetComponent<Model>()->getMaterial()->SetFloat("uNoiseSize", 2.0f);
	trees->GetComponent<Model>()->getMaterial()->SetInteger("uLongNumber", 50);
	trees->GetComponent<Model>()->getMaterial()->SetInteger("uLatNumber", 25);
	
	rockPlanet->getTransform3D()->addLocationX(17.0f); 
	rockPlanet->getTransform3D()->addRotation(Vector3(35.0f, 50.0f, 0.0f));
	rockPlanet->GetComponent<Model>()->getMaterial()->setDrawOption(DrawOption::TESSELATION);
	rockPlanet->GetComponent<Model>()->getMaterial()->SetFloat("uSphereRadius", 0.20f);
	rockPlanet->GetComponent<Model>()->getMaterial()->SetFloat("uNoiseStrength", 0.1f);
	rockPlanet->GetComponent<Model>()->getMaterial()->SetFloat("uNoiseSize", 3.0f);
	
	asteroids->getTransform3D()->setScale(0.1f);
	asteroids->GetComponent<Model>()->getMaterial()->setDrawOption(DrawOption::INSTANCED);
	asteroids->GetComponent<Model>()->getMaterial()->SetInteger("uInstances", 100 * 100);
	asteroids->GetComponent<Model>()->getMaterial()->SetFloat("uSpeed", 0.00001f);
	asteroids->GetComponent<Model>()->getMaterial()->SetFloat("uUpSize", 30.0f);
	asteroids->GetComponent<Model>()->getMaterial()->SetFloat("uInteriorRingDist", 250.0f);
	asteroids->GetComponent<Model>()->getMaterial()->SetFloat("uExteriorRingDist", 500.0f);
	
	stars->getTransform3D()->setScale(0.01f);
	stars->GetComponent<Model>()->getMaterial()->setDrawOption(DrawOption::INSTANCED);
	stars->GetComponent<Model>()->getMaterial()->SetInteger("uInstances", 100 * 100);
	stars->GetComponent<Model>()->getMaterial()->SetFloat("uDistanceRadius", 50.0f);
	stars->GetComponent<Model>()->getMaterial()->SetFloat("uMeshInvScale", 100.0f);
}

void Scene_Cube::Update(float _deltaTime)
{
	Scene::Update(_deltaTime);
}

void Scene_Cube::Close()
{
	Scene::Close();
}