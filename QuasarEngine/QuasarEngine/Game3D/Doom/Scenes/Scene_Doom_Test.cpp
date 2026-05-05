#include "Scene_Doom_Test.h"

#include "Engine/.Prefabs/Object.h"
#include "Engine/3D/cCollider3D.h"
#include "Engine/Utilitaries/Log.h"

#include "Engine/Render/Shaders/Shader.h"
#include "Engine/Render/RendererGl.h"
#include "Game3D/Doom/Actors/Map.h"
#include "Game3D/Bowling/Actors/Player3D.h"
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
    
    //Load Map
    mMap = new Map("Resources/Miscellaneous/Doom/TestMap_2.map");
    
    //Load Actors
    Actor* player = AddActor(new DoomPlayer());
    Actor* skysphere = AddActor(new Object("SkySphere", OBJ_SkySphere, PNG_Doom_1_1_Sky, PROG_BasicModel));

    //Modify Actors
    player->getTransform3D()->addLocationZ(1.0f);
    player->getTransform3D()->addRotationZ(180.0f);
    
    skysphere->GetComponent<Collider3D>()->setActive(false);
}

void Scene_Doom_Test::Update(float _deltaTime)
{
    Scene::Update(_deltaTime);
}

void Scene_Doom_Test::Draw()
{
    Scene::Draw();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	
    ShaderProgram* shader = Assets::GetShaderProgram(PROG_BasicModel);
    shader->Use();
    shader->SetMatrix4Row("uViewProj", dynamic_cast<RendererGl*>(pRenderer)->getViewMatrix());

    mMap->Draw(shader);
}

void Scene_Doom_Test::Close()
{
    Scene::Close();
    delete mMap;
    mMap = nullptr;
}
