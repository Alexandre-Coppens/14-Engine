#pragma once
#include "Engine/Actor.h"

class DoomBaseActor : public Actor
{
public:
    inline DoomBaseActor() : Actor() {};
    inline ~DoomBaseActor() override {};

    virtual void Initialize()               override {Actor::Initialize();}
    virtual void Start()					override {Actor::Start();}
    virtual void Update(float _deltaTime)	override {Actor::Update(_deltaTime);}
    virtual void Destroy()					override {Actor::Destroy();}

    virtual void Interact() {};
    virtual void Shoot() {};
};
