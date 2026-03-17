#pragma once

#include "Engine/Actor.h"
#include "Engine/3D/cModel.h"
#include "Engine/3D/cPhysicBody.h"

class Pin : public Actor
{
private:
    Model* mModel;
    PhysicBody* mPhysicBody;
	
public:
    Model* getModel() const {return mModel;}

private:
public:
    Pin();
    ~Pin() override;

    void Start()					override;
    void Update(float _deltaTime)	override;
    void Destroy()					override;
};
