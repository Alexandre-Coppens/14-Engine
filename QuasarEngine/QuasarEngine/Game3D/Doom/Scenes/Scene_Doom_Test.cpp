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
    Assets::LoadShader(std::vector<GENERATED_SHADERS>{VERT_BasicModel, FRAG_BasicModel}, "BasicModel", DrawOption::TEXTURE);
    Assets::LoadShader(std::vector<GENERATED_SHADERS>{VERT_NoiseHeight, TESC_NoiseHeight, TESE_NoiseHeight, FRAG_NoiseHeight}, "NoiseHeight", DrawOption::TESSELATION);
    Assets::LoadShader(std::vector<GENERATED_SHADERS>{VERT_Geometry, GEOM_Geometry, FRAG_Geometry}, "Geometry", DrawOption::GEOMETRY);

    //Load Actors
    Actor* player = AddActor(new DoomPlayer());

    Actor* cube = AddActor(new Object("Cube", OBJ_cube, PNG_Block, "BasicModel"));
    Actor* cube1 = AddActor(new Object("Cube1", OBJ_cube, PNG_Block, "Geometry"));

    Actor* floor = AddActor(new Object("Floor", OBJ_Plane, PNG_Voronoi, "NoiseHeight"));

    //Start the new Actors to modify them
    InitNewActors();

    //Modify Actors
    player->getTransform3D()->addLocationZ(0.2f);
    
    cube->getTransform3D()->addLocationZ(-0.1f);
    cube1->getTransform3D()->addLocationZ(-0.1f);
    cube1->getTransform3D()->addLocationX(1.0f);
    
    floor->getTransform3D()->setScale(Vector3(5.0f, 5.0f, 0.01f));
}

void Scene_Doom_Test::Update(float _deltaTime)
{
    Scene::Update(_deltaTime);
}

void Scene_Doom_Test::Close()
{
    Scene::Close();
}
