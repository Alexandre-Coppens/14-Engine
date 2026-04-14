#include "Scene_Doom_Test.h"

#include "Engine/.Prefabs/Object.h"
#include "Engine/3D/cCollider3D.h"
#include "Engine/Utilitaries/Assets.h"
#include "Engine/Utilitaries/Log.h"

#include "Engine/Render/Shader.h"
#include "Engine/Render/ShaderProgram.h"
#include "Engine/Render/RendererGl.h"
#include "Game3D/Doom/Actors/DoomPlayer.h"
#include "Game3D/Doom/Actors/Door.h"
#include "Game3D/Doom/Actors/Switch.h"
#include "Game3D/Doom/Actors/Target.h"

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
    Assets::LoadShader(std::vector<GENERATED_SHADERS>{VERT_Simple, FRAG_Simple}, "Simple", DrawOption::COLOR);
    Assets::LoadShader(std::vector<GENERATED_SHADERS>{VERT_NoiseHeight, TESC_NoiseHeight, TESE_NoiseHeight, FRAG_NoiseHeight}, "NoiseHeight", DrawOption::TESSELATION);
    Assets::LoadShader(std::vector<GENERATED_SHADERS>{VERT_Geometry, GEOM_Geometry, FRAG_Geometry}, "Geometry", DrawOption::GEOMETRY);
    Assets::LoadShader(std::vector<GENERATED_SHADERS>{VERT_Grass, FRAG_Grass}, "Grass", DrawOption::INSTANCED);
    Assets::LoadShader(std::vector<GENERATED_SHADERS>{VERT_BasicModel, FRAG_Transparency}, "Transparent", DrawOption::TEXTURE);
    
    //Load Actors
    Actor* player = AddActor(new DoomPlayer());

    Actor* door = AddActor(new Door());
    Actor* lever = AddActor(new Switch(dynamic_cast<Door*>(door)));
    Actor* target = AddActor(new Target());
    Actor* grass = AddActor(new Object("Grass", OBJ_Grass, PNG_Grass_Gradient, "Grass"));

    Actor* floor = AddActor(new Object("Floor", OBJ_Plane, PNG_Voronoi, "NoiseHeight"));

    //Modify Actors
    player->getTransform3D()->addLocationZ(1.0f);
    player->getTransform3D()->addRotationZ(180.0f);

    lever->getTransform3D()->setLocation(Vector3{1.0f, 0.0f, 0.5f});
    lever->getTransform3D()->addRotationY(90.0f);
    
    target->getTransform3D()->addLocationX(-2.0f);
    //target->getTransform3D()->addLocationZ(0.5f);
    
    grass->GetComponent<Collider3D>()->setActive(false);
    
    floor->getTransform3D()->setScale(Vector3(20.0f, 20.0f, 0.01f));
}

void Scene_Doom_Test::Update(float _deltaTime)
{
    Scene::Update(_deltaTime);
}

void Scene_Doom_Test::Close()
{
    Scene::Close();
}
