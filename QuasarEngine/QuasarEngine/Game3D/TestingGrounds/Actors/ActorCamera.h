#pragma once

#include "Engine/Actor.h"

class Camera;
class ActorCamera : public Actor
{
private:
	Camera* mCamera;

public:

private:
public:
	ActorCamera();
	~ActorCamera() override;

	void Start()					override;
	void Update(float _deltaTime)	override;
	void Destroy()					override;
};
