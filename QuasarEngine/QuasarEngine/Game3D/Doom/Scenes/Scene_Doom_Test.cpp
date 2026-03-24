#include "Scene_Doom_Test.h"

#include "Engine/.Prefabs/Object.h"
#include "Engine/Utilitaries/Assets.h"
#include "Engine/Utilitaries/Log.h"

#include "Engine/Render/Shader.h"
#include "Engine/Render/ShaderProgram.h"
#include "Engine/Render/RendererGl.h"
#include "Game3D/Doom/Actors/DoomPlayer.h"

Scene_Doom_Test::Scene_Doom_Test(std::string _name)
{
}

Scene_Doom_Test::~Scene_Doom_Test()
{
}

void Scene_Doom_Test::Start()
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
    Assets::LoadShader(VERT_BasicModel, FRAG_BasicModel, "BasicModel", TEXTURE);
    Assets::LoadShader(VERT_SimpleTess, TESC_SimpleTess, TESE_SimpleTess, FRAG_SimpleTess, "SimpleTess", TEXTURE);

    //Load Actors
    Actor* player = AddActor(new DoomPlayer());

    Actor* floor = AddActor(new Object("Floor", "Cube", "Block", "BasicModel"));
    Actor* floor1 = AddActor(new Object("Floor1", "Cube", "Block", "BasicModel"));

    Actor* tunnelb = AddActor(new Object("tunnelb", "Plane", "Block", "BasicModel"));

    //Start the new Actors to modify them
    InitNewActors();

    //Modify Actors
    player->getTransform3D()->addLocationZ(0.2f);
    
    floor->getTransform3D()->addLocationZ(-0.1f);
    floor1->getTransform3D()->addLocationZ(-0.1f);
    floor1->getTransform3D()->addLocationX(1.0f);
    
    tunnelb->getTransform3D()->setScale(Vector3(10.0f, 10.0f, 0.01f));
}

void Scene_Doom_Test::Update(float _deltaTime)
{
    Scene::Update(_deltaTime);
}

void Scene_Doom_Test::Close()
{
    Scene::Close();
}
