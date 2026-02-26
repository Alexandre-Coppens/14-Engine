#pragma once

#include "Engine/Actor.h"
#include "Engine/cModel.h"

class Pin : public Actor
{
private:
    Model* mModel;
	
public:
    Model* getModel() const {return mModel;}

private:
public:
    Pin();
    ~Pin();

    void Start()					override;
    void Update(float _deltaTime)	override;
    void Destroy()					override;
};
