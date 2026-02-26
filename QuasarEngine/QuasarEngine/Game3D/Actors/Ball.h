#pragma once

#include "Engine/Actor.h"
#include "Engine/cModel.h"

class Ball : public Actor
{
private:
    Model* mModel;
	
public:
    Model* getModel() const {return mModel;}

private:
public:
    Ball();
    ~Ball();

    void Start()					override;
    void Update(float _deltaTime)	override;
    void Destroy()					override;
};
