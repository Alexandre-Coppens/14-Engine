#pragma once

#include "Actor.h"

class Player3D : public Actor
{
public:
    Player3D();
    ~Player3D();

    void Start()					override;
    void Update(float _deltaTime)	override;
    void Destroy()					override;
};
