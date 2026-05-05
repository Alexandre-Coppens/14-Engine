#pragma once
#include "Engine/Scene.h"

class Preset_Scene : public Scene
{
private:

protected:

public:
    Preset_Scene(std::string _name);
    ~Preset_Scene() override;

    void Start()					override;
    void Update(float _deltaTime)	override;
    void Close()					override;
};