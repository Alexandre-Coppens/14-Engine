#pragma once
#include "Engine/Actor.h"

class Model;

class BowlingAlley : public Actor
{
private:
public:

private:
public:
    BowlingAlley();
    ~BowlingAlley();

    void Start()					override;
    void Update(float _deltaTime)	override;
    void Destroy()					override;
};