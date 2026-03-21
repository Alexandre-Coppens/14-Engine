#pragma once
#include "Engine/Scene.h"

class Scene_Doom_Test : public Scene
{
private:

protected:

public:
    Scene_Doom_Test(std::string _name);
    ~Scene_Doom_Test() override;

    void Start()					override;
    void Update(float _deltaTime)	override;
    void Close()					override;
};