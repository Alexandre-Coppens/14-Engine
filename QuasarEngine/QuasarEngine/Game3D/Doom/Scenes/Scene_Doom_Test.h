#pragma once
#include "Engine/Scene.h"
#include "Game3D/Doom/Actors/Map.h"

class Scene_Doom_Test : public Scene
{
private:
    Map* mMap;

public:
    Scene_Doom_Test(std::string _name);
    ~Scene_Doom_Test() override;

    void Start()					override;
    void Update(float _deltaTime)	override;
    void Draw()	                    override;
    void Close()					override;
};
