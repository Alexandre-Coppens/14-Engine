#pragma once

#include "Engine/Actor.h"

class Camera;
class Player3D : public Actor
{
private:
    Camera* pCamera;
    
public:
    Player3D();
    ~Player3D();

    void Start()					override;
    void Update(float _deltaTime)	override;
    void Destroy()					override;
};
