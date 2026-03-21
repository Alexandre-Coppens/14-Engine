#include "Preset_Scene.h"

#include "Engine/Utilitaries/Assets.h"
#include "Engine/Utilitaries/Log.h"

#include "Engine/Render/Shader.h"
#include "Engine/Render/ShaderProgram.h"
#include "Engine/Render/RendererGl.h"

Preset_Scene::Preset_Scene(std::string _name)
{
}

Preset_Scene::~Preset_Scene()
{
}

void Preset_Scene::Start()
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

    //LoadModels

    //Load Textures

    //Load Actors

    //Start the new Actors to modify them
    InitNewActors();

    //Modify Actors
}

void Preset_Scene::Update(float _deltaTime)
{
    Scene::Update(_deltaTime);
}

void Preset_Scene::Close()
{
    Scene::Close();
}